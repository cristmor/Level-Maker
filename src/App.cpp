#include "App.hpp"
#include "EntityManager.hpp"
#include "GameState.hpp"

App::App() {
	setTextSetting();
}

App::~App() {
}

// Public
void App::run() {
	static sf::RenderWindow& window = GameState::getInstance().window();

	static sf::Vector2i& mousePosition = AppState::getInstance().mousePosition();
	static sf::Vector2i& cameraPosition = AppState::getInstance().cameraPosition();
	static sf::VertexArray& grid = AppState::getInstance().grid();

	sf::Clock clock;
	while(window.isOpen()) {
		mousePosition = sf::Mouse::getPosition(window);

		mInterface.update();

		inputs();
		movements();
		render();
		setEntity();
		setAnimation();
		setLayer();
		saveLevel();
		loadLevel();

		sf::View view = window.getView();
		view.setCenter(cameraPosition.x, cameraPosition.y);
		window.setView(view);


		grid.clear();
		sf::VertexArray vertices(sf::Lines);
		int RECT_SIZE = (16 * SCALE);


		// Looping through, but starting relative to the center position
		for (int x = cameraPosition.x - (WINDOW_SIZE_X / 2.0) - (SCALE * 32); x <= cameraPosition.x + (WINDOW_SIZE_X / 2.0) + (SCALE * 32); x += RECT_SIZE) {
		    for (int y = cameraPosition.y - (WINDOW_SIZE_Y / 2.0) - (SCALE * 32); y <= cameraPosition.y + (WINDOW_SIZE_Y / 2.0) +(SCALE * 32); y += RECT_SIZE) {
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

		grid = vertices;
	}
}

// Private
void App::render() {
	static sf::RenderWindow& window = GameState::getInstance().window();
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();

	static sf::VertexArray& grid = AppState::getInstance().grid();
	static sf::Text& textPosition = AppState::getInstance().textPosition();
	static bool& showGrid = AppState::getInstance().showGrid();
	static bool& followMouse = AppState::getInstance().followMouse();

	sortEntitiesByLayer();
	window.clear();
	if(showGrid) {
		window.draw(grid);
	}

	for(auto& entity : entities) {
		if(entity->tag() != "") {
			/*
			Vec2& position = entity->movement().position;
			entity->animation().sprite().setPosition(position.x, position.y);
			entity->animation().update();
			fWindow->draw(entity->animation().sprite());
			*/
		}
	}

	if(followMouse) {
		window.draw(textPosition);
	}
	ImGui::SFML::Render(window);
	window.display();
}

void App::inputs() {
	static sf::RenderWindow& window = GameState::getInstance().window();

	static sf::Vector2i& cameraPosition = AppState::getInstance().cameraPosition();
	static std::ofstream& output = AppState::getInstance().output();
	static bool& followMouse = AppState::getInstance().followMouse();
	static bool& newEntity = AppState::getInstance().newEntity();


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
				followMouse = false;
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
		cameraPosition += { 0, -1 };
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		cameraPosition += { 0, 1 };
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		cameraPosition += { -1, 0 };
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		cameraPosition += { 1, 0 };
	}
}

void App::movements() {
	static bool& followMouse = AppState::getInstance().followMouse();
	if(followMouse) {
		/*
		auto& entityP = fCurrentEntity->movement().position;
		auto& entityBB = fCurrentEntity->boundingBox().halfSize;
		auto textBB = fTextPosition.getGlobalBounds().getSize();

		auto newPosition = fMousePosition;

		if(fInterface->snapGrid()) {
			newPosition.x = newPosition.x + (16 * SCALE)/2 - (newPosition.x%static_cast<int>(16 * SCALE));
			newPosition.y = newPosition.y + (16 * SCALE)/2 - (newPosition.y%static_cast<int>(16 * SCALE));
		}

		entityP = {static_cast<float>(newPosition.x), static_cast<float>(newPosition.y)};
		fTextPosition.setPosition(entityP.x - textBB.x/2, entityP.y - entityBB.y - textBB.y - 5);
		fTextPosition.setString("(" + std::to_string(static_cast<int>(entityP.x)) + "," + std::to_string(static_cast<int>(entityP.y)) + ")");
		*/
	}
}

void App::setEntity() {
	static bool& newEntity = AppState::getInstance().newEntity();
	if(newEntity) {
		/*
		fInterface->createEntity() = false;
		fInterface->followMouse() = true;
		fCurrentEntity = std::make_shared<Entity>(fAssets->getEntity(fInterface->getEntityTag()));
		fCurrentEntity->animation().layer() = fInterface->layer();
		fInterface->setAnimationTag(fCurrentEntity->animation().tag());
		fEntityVector.push_back(fCurrentEntity);
	}

	if (fInterface->deleteEntity()) {
		for (int i = 0;i < fEntityVector.size();i++) {
			if (fCurrentEntity == fEntityVector[i]) {
				fEntityVector.erase(fEntityVector.begin() + i);
			}
		}
		if(fEntityVector.size()) {
			fCurrentEntity = fEntityVector.back();
			fInterface->setEntityTag(fCurrentEntity->tag());
			fInterface->setAnimationTag(fCurrentEntity->animation().tag());
		}
		else {
			fCurrentEntity = std::make_shared<Entity>();
			fInterface->followMouse() = false;
		}
		fInterface->deleteEntity() = false;
		*/
	}
}

void App::setAnimation() {
	/*
	if(fCurrentEntity && fInterface->getAnimation() != fCurrentEntity->animation().tag()) {
		fCurrentEntity->animation() = fAssets->getAnimation(fInterface->getAnimation());
	}
	*/
}

void App::setLayer() {
	/*
	if(fCurrentEntity && fInterface->layer() != fCurrentEntity->animation().layer()) {
		//fCurrentEntity->animation().layer() = fInterface->layer();
	}
	*/
}

void App::selectEntity() {
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();
	for(auto& entity: entities) {
		if(entity) {
			/*
			auto entityBB = entity->boundingBox().halfSize;
			auto entityP = entity->movement().position;
			if(fMousePosition.x >= (entityP.x - entityBB.x) && fMousePosition.x <= (entityBB.x + entityP.x) &&
			   fMousePosition.y >= (entityP.y - entityBB.y) && fMousePosition.y <= (entityBB.y + entityP.y)) {
				fCurrentEntity = entity;
				fInterface->followMouse() = true;
				fInterface->setEntityTag(fCurrentEntity->tag());
				fInterface->setAnimationTag(fCurrentEntity->animation().tag());
				fInterface->setLayer(fCurrentEntity->animation().layer());
			}
			*/
		}
	}
}

void App::saveLevel() {
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();

	static bool& save = AppState::getInstance().save();
	static std::string& filename = AppState::getInstance().filename();

	if(save) {
		std::cout << "Saved level to " << filename << std::endl;
		std::ofstream file;
		file.open(filename);

		for(auto& entity : entities) {
			/*
			file << entity->movement().position.x << " "
				<< entity->movement().position.y << " "
				<< entity->tag() << " "
				<< entity->animation().tag() << " "
				<< entity->animation().layer() << std::endl;

			std::cout << entity->movement().position.x << " "
				<< entity->movement().position.y << " "
				<< entity->tag() << " "
				<< entity->animation().tag() << " "
				<< entity->animation().layer() << std::endl;
			*/
		}

		file.close();
		
		save = false;
	}
}

void App::loadLevel() {
	static bool& load = AppState::getInstance().load();
	static std::string& filename = AppState::getInstance().filename();
	static std::shared_ptr<Entity>& currentEntity = AppState::getInstance().currentEntity();

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


			/*
			fCurrentEntity = std::make_shared<Entity>(fAssets->getEntity(out.eTag));
			fCurrentEntity->animation() = fAssets->getAnimation(out.aTag);
			fCurrentEntity->movement().position = {static_cast<float>(out.x), static_cast<float>(out.y)};
			fCurrentEntity->movement().prevPosition = fCurrentEntity->movement().position;
			fCurrentEntity->animation().layer() = out.layer;
			fInterface->setLayer(out.layer);

			fEntityVector.push_back(fCurrentEntity);
			*/
		}

		file.close();

		load = false;

		// Change this
		//fCurrentEntity = fEntityVector[0];
	}
}

void App::setTextSetting() {
	static sf::Font& font = AppState::getInstance().font();
	static sf::Text& textPosition = AppState::getInstance().textPosition();
	if(!font.loadFromFile("/home/cristmor/dev/cpp/LevelMaker/deps/imgui/misc/fonts/Roboto-Medium.ttf")) {
		std::cerr << "Error: Unable to font" << std::endl; 
	}

	textPosition.setFont(font);
	textPosition.setString("test");
	textPosition.setCharacterSize(12);
	textPosition.setFillColor(sf::Color::White);
	textPosition.setPosition(200.0f, 200.0f);
}

void App::sortEntitiesByLayer() {
	// Change this
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();
	for(size_t x = 0;x < entities.size(); x++) {
		for(size_t y = 0; y < entities.size() - 1;y++) {
			/*
			if(fEntityVector[y]->animation().layer() > fEntityVector[y+1]->animation().layer()) {
				std::shared_ptr<Entity> temp = fEntityVector[y];
				fEntityVector[y] = fEntityVector[y+1];
				fEntityVector[y+1] = temp;
			}
			*/
		}
	}
}
