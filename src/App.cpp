#include "App.hpp"

App::App() {
}

App::~App() {
}

// Public
void App::run() {
	static sf::RenderWindow& window = GameState::getInstance().window();
	static EntityManager& entityManager = GameState::getInstance().entityManager();
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();
	static Assets& assets = GameState::getInstance().assets();
	static int& layer = AppState::getInstance().layer();

	static bool& followMouse = AppState::getInstance().followMouse();
	static sf::Vector2i& mousePosition = AppState::getInstance().mousePosition();
	static sf::Vector2i& cameraPosition = AppState::getInstance().cameraPosition();
	static std::string& entityTag = AppState::getInstance().entityTag();
	static std::string& animationTag = AppState::getInstance().animtionTag();
	static std::ofstream& output = AppState::getInstance().output();
	static bool& newEntity = AppState::getInstance().newEntity();
	static bool& deleteEntity = AppState::getInstance().deleteEntity();
	static bool& snapGrid = AppState::getInstance().snapGrid();
	static bool& showGrid = AppState::getInstance().showGrid();

	sf::Clock clock;

	//
	// Main Program Loop
	//
	while(window.isOpen()) {
		mousePosition = sf::Mouse::getPosition(window);

		mInterface.update();

		//
		// Inputs
		//
		sf::Event event;
		while(window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);
			if(event.type == sf::Event::Closed) {
				output.close();
				window.close();
			}
			if(event.type == sf::Event::MouseButtonPressed) {
				if(event.mouseButton.button == sf::Mouse::Left) {
					selectEntity();
				}
				if(event.mouseButton.button == sf::Mouse::Right) {
					followMouse = !followMouse;
				}
			}
			if(event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::R) {
					newEntity = true;
				}
			}	
			/*
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Enter) {
				}
			}
			*/
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			cameraPosition += { 0, -5 };
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			cameraPosition += { 0, 5 };
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			cameraPosition += { -5, 0 };
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			cameraPosition += { 5, 0 };
		}

		//
		// Movement
		//
		if(mCurrentEntity) {
			//std::cout << "x: " << currentEntity->position().x << ", y: " << currentEntity->position().y << std::endl;
		}
		if(followMouse) {
			auto& entityP = mCurrentEntity->position();
			auto& entityBB = mCurrentEntity->boundingBox();
			auto textBB = mTextPosition.getGlobalBounds().getSize();
			auto newPosition = mousePosition + cameraPosition;
			if(snapGrid) {
				newPosition.x = newPosition.x + (16 * SCALE)/2 - (newPosition.x%static_cast<int>(16 * SCALE));
				newPosition.y = newPosition.y + (16 * SCALE)/2 - (newPosition.y%static_cast<int>(16 * SCALE));
			}
			mCurrentEntity->setPosition({static_cast<float>(newPosition.x), static_cast<float>(newPosition.y)});
			mTextPosition.setPosition(entityP.x - textBB.x, entityP.y - entityBB.y/2 - textBB.y - 5);
			mTextPosition.setString("(" + std::to_string(static_cast<int>(entityP.x)) + "," + std::to_string(static_cast<int>(entityP.y)) + ")");
		}

		//
		// Render
		//
		//sortEntitiesByLayer();
		window.clear();
		if(showGrid) {
			window.draw(mGrid);
		}
		mRenderer.render();
		if(followMouse) {
			window.draw(mTextPosition);
		}
		ImGui::SFML::Render(window);
		window.display();

		//
		// Set Entity
		//
		if(newEntity) {
			newEntity = false;
			followMouse = true;
			mCurrentEntity = entityManager.addEntity(entityTag, { 0, 0 }, { 0, 0 }, assets.getAnimation(animationTag));
			mCurrentEntity->layer = layer;
		}
		if (deleteEntity) {
			if(entityManager.entities().size()) {
				// may need to change this
				entityManager.deleteEntity("", mCurrentEntity->copyNo());
				for(size_t i = entityManager.entities().size() - 1;i > 0;i--) {
					if(entityManager.entities()[i]) {
						mCurrentEntity = entityManager.entities()[i];
						break;
					}
					else {
						mCurrentEntity = std::make_shared<Entity>();
						followMouse = false;
					}
				}
				
				entityTag = mCurrentEntity->tag();
				animationTag = mCurrentEntity->animationTag();
			}
			else {
				mCurrentEntity = std::make_shared<Entity>();
				followMouse = false;
			}
			deleteEntity = false;
		}
		if(mCurrentEntity) {
			if(mCurrentEntity->animationTag() != animationTag) {
				mCurrentEntity->setAnimation(assets.getAnimation(animationTag));
			}
			if(mCurrentEntity->layer != layer) {
				mCurrentEntity->layer = layer;
			}
		}

		//
		// Level
		//
		// Save
		static bool& save = AppState::getInstance().save();
		static std::string& filename = AppState::getInstance().filename();
		if(save) {
			std::cout << "Saved level to " << filename << std::endl;
			std::ofstream file;
			file.open(filename);

			for(auto& entity : entities) {
				file << entity->position().x << " "
					<< entity->position().y << " "
					<< entity->tag() << " "
					<< entity->animationTag() << " "
					<< entity->layer << std::endl;

				std::cout << entity->position().x << " "
					<< entity->position().y << " "
					<< entity->tag() << " "
					<< entity->animationTag() << " "
					<< entity->layer << std::endl;
			}

			file.close();
			
			save = false;
		}
		// Load
		static bool& load = AppState::getInstance().load();
		if(load) {
			std::cout << "Load level from " << filename << std::endl;
			std::ifstream file(filename);
			Output out;
			while(file.good()) {
				file >> out.x
					>> out.y
					>> out.eTag
					>> out.aTag
					>> out.layer;
			std::cout << out.x << " "
					<< out.y << " "
					<< out.eTag << " "
					<< out.aTag << " "
					<< out.layer << " "
					<< std::endl;

				entityManager.addEntity(out.eTag, { out.x, out.y }, { 0, 0}, assets.getAnimation(out.aTag), out.layer, false);
			}
			mCurrentEntity = entityManager.entities().back();
			file.close();
			load = false;
			// Change this
			//fCurrentEntity = fEntityVector[0];
		}

		//
		// Position overlay
		//
		if(!mFont.loadFromFile("/home/cristmor/dev/cpp/LevelMaker/deps/imgui/misc/fonts/Roboto-Medium.ttf")) {
			std::cerr << "Error: Unable to font" << std::endl; 
		}
		mTextPosition.setFont(mFont);
		mTextPosition.setString("test");
		mTextPosition.setCharacterSize(12);
		mTextPosition.setFillColor(sf::Color::White);
		mTextPosition.setPosition(200.0f, 200.0f);

		//
		// Camera View Update
		//
		sf::View view = window.getView();
		view.setCenter( cameraPosition.x + WINDOW_SIZE_X/2.0, cameraPosition.y + WINDOW_SIZE_Y/2.0);
		window.setView(view);

		//
		// Grid
		//
		if(showGrid) {
			mGrid.clear();
			sf::VertexArray vertices(sf::Lines);
			int RECT_SIZE = (16 * SCALE);
			// Looping through, but starting relative to the center position
			for (int x = cameraPosition.x - (WINDOW_SIZE_X / 2.0) - (SCALE * 32); x <= cameraPosition.x + (WINDOW_SIZE_X) + (SCALE * 32); x += RECT_SIZE) {
			    for (int y = cameraPosition.y - (WINDOW_SIZE_Y / 2.0) - (SCALE * 32); y <= cameraPosition.y + (WINDOW_SIZE_Y) + (SCALE * 32); y += RECT_SIZE) {
				sf::Vector2f topLeft(static_cast<float>(x), static_cast<float>(y));
				sf::Vector2f bottomRight(topLeft.x + RECT_SIZE, topLeft.y + RECT_SIZE);
				topLeft.x += (16 * SCALE) - (static_cast<int>(topLeft.x)%static_cast<int>(16 * SCALE));
				topLeft.y += (16 * SCALE) - (static_cast<int>(topLeft.y)%static_cast<int>(16 * SCALE));
				bottomRight.x += (16 * SCALE) - (static_cast<int>(bottomRight.x)%static_cast<int>(16 * SCALE));
				bottomRight.y += (16 * SCALE) - (static_cast<int>(bottomRight.y)%static_cast<int>(16 * SCALE));
				// Add the four lines (outline) of each rectangle
				vertices.append(sf::Vertex(topLeft, sf::Color::White));
				vertices.append(sf::Vertex({bottomRight.x, topLeft.y}, sf::Color::White));
				vertices.append(sf::Vertex({bottomRight.x, topLeft.y}, sf::Color::White));
				vertices.append(sf::Vertex(bottomRight, sf::Color::White));
				vertices.append(sf::Vertex(bottomRight, sf::Color::White));
				vertices.append(sf::Vertex({topLeft.x, bottomRight.y}, sf::Color::White));
				vertices.append(sf::Vertex({topLeft.x, bottomRight.y}, sf::Color::White));
				vertices.append(sf::Vertex(topLeft, sf::Color::White));
			    }
			}
			mGrid = vertices;
		}

	}
}

// Private
void App::selectEntity() {
	static EntityManager& entityManager = GameState::getInstance().entityManager();
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();

	static sf::Vector2i& mousePosition = AppState::getInstance().mousePosition();
	static sf::Vector2i& cameraPosition = AppState::getInstance().cameraPosition();
	static std::string& entityTag = AppState::getInstance().entityTag();
	static std::string& animationTag = AppState::getInstance().animtionTag();
	static int& layer = AppState::getInstance().layer();
	static bool& followMouse = AppState::getInstance().followMouse();

	auto newMousePosition = mousePosition + cameraPosition;
	for(auto& entity: entities) {
		if(entity) {
			auto entityBB = entity->boundingBox(); // need for half-Size
			auto entityP = entity->position();
			if(newMousePosition.x >= (entityP.x - entityBB.x/2) && newMousePosition.x <= (entityBB.x/2 + entityP.x) &&
			   newMousePosition.y >= (entityP.y - entityBB.y/2) && newMousePosition.y <= (entityBB.y/2 + entityP.y)) {
				mCurrentEntity = entity;
				followMouse = true;
				// May need to change this
				entityTag = mCurrentEntity->tag();
				animationTag = mCurrentEntity->animationTag();
				layer = mCurrentEntity->layer;
			}
		}
	}
}

void App::sortEntitiesByLayer() {
	// Change this
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();
	/*
	for(size_t x = 0;x < entities.size(); x++) {
		for(size_t y = 0; y < entities.size() - 1;y++) {
			if(fEntityVector[y]->animation().layer() > fEntityVector[y+1]->animation().layer()) {
				std::shared_ptr<Entity> temp = fEntityVector[y];
				fEntityVector[y] = fEntityVector[y+1];
				fEntityVector[y+1] = temp;
			}
		}
	}
	*/
}
