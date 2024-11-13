#include "App.hpp"
#include "Assets.hpp"
#include "EntityManager.hpp"
#include "GameState.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include <exception>

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
		saveLevel();
		loadLevel();

		sf::View view = window.getView();
		view.setCenter( cameraPosition.x + WINDOW_SIZE_X/2.0, cameraPosition.y + WINDOW_SIZE_Y/2.0);
		window.setView(view);

		grid.clear();
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

		grid = vertices;
	}
}

// Private
void App::render() {
	static sf::RenderWindow& window = GameState::getInstance().window();

	static sf::VertexArray& grid = AppState::getInstance().grid();
	static sf::Text& textPosition = AppState::getInstance().textPosition();
	static bool& showGrid = AppState::getInstance().showGrid();
	static bool& followMouse = AppState::getInstance().followMouse();

	//sortEntitiesByLayer();
	window.clear();
	if(showGrid) {
		window.draw(grid);
	}

	mRenderer.render();

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
}

void App::movements() {
	static sf::Text& textPosition = AppState::getInstance().textPosition();
	static sf::Vector2i& mousePosition = AppState::getInstance().mousePosition();
	static bool& snapGrid = AppState::getInstance().snapGrid();
	static sf::Vector2i& cameraPosition = AppState::getInstance().cameraPosition();

	static bool& followMouse = AppState::getInstance().followMouse();
	static std::shared_ptr<Entity>& currentEntity = AppState::getInstance().currentEntity();

	if(currentEntity) {
		//std::cout << "x: " << currentEntity->position().x << ", y: " << currentEntity->position().y << std::endl;
	}

	if(followMouse) {
		auto& entityP = currentEntity->position();
		auto& entityBB = currentEntity->boundingBox();
		auto textBB = textPosition.getGlobalBounds().getSize();

		auto newPosition = mousePosition + cameraPosition;

		if(snapGrid) {
			newPosition.x = newPosition.x + (16 * SCALE)/2 - (newPosition.x%static_cast<int>(16 * SCALE));
			newPosition.y = newPosition.y + (16 * SCALE)/2 - (newPosition.y%static_cast<int>(16 * SCALE));
		}

		currentEntity->setPosition({static_cast<float>(newPosition.x), static_cast<float>(newPosition.y)});
		textPosition.setPosition(entityP.x - textBB.x/2, entityP.y - entityBB.y/2 - textBB.y - 5);
		textPosition.setString("(" + std::to_string(static_cast<int>(entityP.x)) + "," + std::to_string(static_cast<int>(entityP.y)) + ")");
	}
}

void App::setEntity() {
	static EntityManager& entityManager = GameState::getInstance().entityManager();
	static Assets& assets = GameState::getInstance().assets();

	static bool& newEntity = AppState::getInstance().newEntity();
	static bool& deleteEntity = AppState::getInstance().deleteEntity();
	static std::string& entityTag = AppState::getInstance().entityTag();
	static std::string& animationTag = AppState::getInstance().animtionTag();
	static int& layer = AppState::getInstance().layer();

	static bool& followMouse = AppState::getInstance().followMouse();
	static std::shared_ptr<Entity>& currentEntity = AppState::getInstance().currentEntity();

	if(newEntity) {
		newEntity = false;
		followMouse = true;
		currentEntity = entityManager.addEntity(entityTag, { 0, 0 }, { 0, 0 }, assets.getAnimation(animationTag));
		currentEntity->layer = layer;
	}

	if (deleteEntity) {
		if(entityManager.entities().size()) {
			// may need to change this
			entityManager.deleteEntity("", currentEntity->copyNo());
			std::cout << "entities.size():" << entityManager.entities().size() << std::endl;
			for(size_t i = entityManager.entities().size() - 1;i > 0;i--) {
				if(entityManager.entities()[i]) {
					currentEntity = entityManager.entities()[i];
					break;
				}
				else {
					currentEntity = std::make_shared<Entity>();
					followMouse = false;
				}
			}
			
			entityTag = currentEntity->tag();
			animationTag = currentEntity->animationTag();
		}
		else {
			currentEntity = std::make_shared<Entity>();
			followMouse = false;
		}
		deleteEntity = false;
	}

	if(currentEntity) {
		if(currentEntity->animationTag() != animationTag) {
			currentEntity->setAnimation(assets.getAnimation(animationTag));
		}
		if(currentEntity->layer != layer) {
			currentEntity->layer = layer;
		}
	}
}

void App::selectEntity() {
	static const EntityVector& entities = GameState::getInstance().entityManager().entities();

	static const sf::Vector2i& mousePosition = AppState::getInstance().mousePosition();
	static sf::Vector2i& cameraPosition = AppState::getInstance().cameraPosition();
	static std::shared_ptr<Entity>& currentEntity = AppState::getInstance().currentEntity();
	static bool& followMouse = AppState::getInstance().followMouse();
	static std::string& entityTag = AppState::getInstance().entityTag();
	static std::string& animationTag = AppState::getInstance().animtionTag();
	static int& layer = AppState::getInstance().layer();

	auto newMousePosition = mousePosition + cameraPosition;

	for(auto& entity: entities) {
		if(entity) {
			auto entityBB = entity->boundingBox(); // need for half-Size
			auto entityP = entity->position();
			if(newMousePosition.x >= (entityP.x - entityBB.x) && newMousePosition.x <= (entityBB.x + entityP.x) &&
			   newMousePosition.y >= (entityP.y - entityBB.y) && newMousePosition.y <= (entityBB.y + entityP.y)) {
				currentEntity = entity;
				followMouse = true;
				// May need to change this
				entityTag = currentEntity->tag();
				animationTag = currentEntity->animationTag();
				layer = currentEntity->layer;
				std::cout << "id:" << currentEntity->copyNo()  << std::endl;
			}
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
}

void App::loadLevel() {
	static EntityManager& entityManager = GameState::getInstance().entityManager();
	static Assets& assets = GameState::getInstance().assets();

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

			entityManager.addEntity(out.eTag, { out.x, out.y }, { 0, 0}, assets.getAnimation(out.aTag), out.layer, false);
		}
		currentEntity = entityManager.entities().back();

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
