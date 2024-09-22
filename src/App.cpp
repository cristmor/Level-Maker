#include "App.h"
#include <SFML/Window/Keyboard.hpp>

App::App() {
	fAssets = std::make_shared<Assets>();
	fWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), WINDOW_TITLE);
	fInterface = std::make_shared<Interface>(fWindow, fAssets);
	fOutput.open(OUTPUT_FILENAME);

	setTextSetting();
}

App::~App() {
}

// Public
void App::run() {
	sf::Clock clock;
	while(fWindow->isOpen()) {
		fMousePosition = sf::Mouse::getPosition(*fWindow);

		fInterface->whileRun();

		inputs();
		movements();
		render();
		setEntity();
		setAnimation();
	}
}

// Private
void App::render() {
	fWindow->clear();
	for(auto& entity: fEntityVector) {
		if(entity->tag() != "") {
			Vec2& position = entity->movement().position;
			entity->animation().sprite().setPosition(position.x, position.y);
			entity->animation().update();
			fWindow->draw(entity->animation().sprite());
		}
	}
	if(fInterface->followMouse()) {
		fWindow->draw(fTextPosition);
	}
	fInterface->render();
	fWindow->display();
}

void App::inputs() {
	sf::Event event;
	while(fWindow->pollEvent(event)) {
		fInterface->events(event);
		if(event.type == sf::Event::Closed) {
			fOutput.close();
			fWindow->close();
		}

		if(event.type == sf::Event::MouseButtonPressed) {
			if(event.mouseButton.button == sf::Mouse::Left) {
				selectEntity();
			}

			if(event.mouseButton.button == sf::Mouse::Right) {
				fInterface->followMouse() = false;
			}
		}

		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Space) {
				bool inverse = !fInterface->followMouse();
				fInterface->followMouse() = inverse;
			}
		}

		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Enter) {
				fInterface->followMouse() = false;
				fCurrentEntity = std::make_shared<Entity>(fAssets->getEntity(fInterface->getEntityTag()));
				fCurrentEntity->movement().position = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
				fCurrentEntity->movement().prevPosition = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
				fEntityVector.push_back(fCurrentEntity);
			}
		}
	}
}

void App::movements() {
	if(fInterface->followMouse()) {
		auto& entityP = fCurrentEntity->movement().position;
		auto& entityBB = fCurrentEntity->boundingBox().halfSize;
		auto textBB = fTextPosition.getGlobalBounds().getSize();
		entityP = {static_cast<float>(fMousePosition.x), static_cast<float>(fMousePosition.y)};
		fTextPosition.setPosition(entityP.x - textBB.x/2, entityP.y - entityBB.y - textBB.y - 5);
		fTextPosition.setString("(" + std::to_string(static_cast<int>(entityP.x)) + "," + std::to_string(static_cast<int>(entityP.y)) + ")");
	}
}

void App::setEntity() {
	if (fInterface->createEntity()) {
		fInterface->createEntity() = false;
		fInterface->followMouse() = true;
		fCurrentEntity = std::make_shared<Entity>(fAssets->getEntity(fInterface->getEntityTag()));
		fEntityVector.push_back(fCurrentEntity);
	}
}

void App::setAnimation() {
	if(fCurrentEntity && fInterface->getAnimation() != fCurrentEntity->animation().tag()) {
		fCurrentEntity->animation() = fAssets->getAnimation(fInterface->getAnimation());
	}
}

void App::selectEntity() {
	for(auto& entity: fEntityVector) {
		if(entity) {
			auto entityBB = entity->boundingBox().halfSize;
			auto entityP = entity->movement().position;
			if(fMousePosition.x >= (entityP.x - entityBB.x) && fMousePosition.x <= (entityBB.x + entityP.x) &&
			   fMousePosition.y >= (entityP.y - entityBB.y) && fMousePosition.y <= (entityBB.y + entityP.y)) {
				fCurrentEntity = entity;
				fInterface->followMouse() = true;
				fInterface->setEntityTag(fCurrentEntity->tag());
				fInterface->setAnimationTag(fCurrentEntity->animation().tag());
			}
		}
	}
}

void App::setTextSetting() {
	if(!fFont.loadFromFile("/home/cristmor/dev/cpp/LevelMaker/deps/imgui/misc/fonts/Roboto-Medium.ttf")) {
		std::cerr << "Error: Unable to font" << std::endl; 
	}

	fTextPosition.setFont(fFont);
	fTextPosition.setString("test");
	fTextPosition.setCharacterSize(12);
	fTextPosition.setFillColor(sf::Color::White);
	fTextPosition.setPosition(200.0f, 200.0f);
}
