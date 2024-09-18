#include "App.h"
#include <SFML/Window/Keyboard.hpp>

App::App() {
	fAssets = std::make_shared<Assets>();
	fWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), WINDOW_TITLE);
	fInterface = std::make_shared<Interface>(fWindow, fAssets);
	fOutput.open(OUTPUT_FILENAME);

	fCurrentEntity = std::make_shared<Entity>(fAssets->getEntity(fInterface->getEntityTag()));
	fCurrentEntity->movement().position = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
	fCurrentEntity->movement().prevPosition = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
	fEntityVector.push_back(fCurrentEntity);
}

App::~App() {
}

// Public
void App::run() {
	sf::Clock clock;
	while(fWindow->isOpen()) {

		fInterface->whileRun();

		inputs();
		movements();
		render();
		setEntity();
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
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*fWindow);
		fCurrentEntity->movement().position = {static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)};
	}
}

void App::setEntity() {
	if(fInterface->getEntityTag() == "") {
		return;
	}

	if (fCurrentEntity->tag() != fInterface->getEntityTag()) {
		*fCurrentEntity = fAssets->getEntity(fInterface->getEntityTag());
		fCurrentEntity->movement().position = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
		fCurrentEntity->movement().prevPosition = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
	}
}

