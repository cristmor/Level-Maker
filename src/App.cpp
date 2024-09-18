#include "App.h"

App::App() {
	fAssets = std::make_shared<Assets>();
	fWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), WINDOW_TITLE);
	fInterface = std::make_shared<Interface>(fWindow, fAssets);
	fOutput.open(OUTPUT_FILENAME);

	fEntity = std::make_shared<Entity>();
}

App::~App() {
}

// Public
void App::run() {
	sf::Clock clock;
	while(fWindow->isOpen()) {

		fInterface->whileRun();

		inputs();
		render();
		setEntity();
	}
}

// Private
void App::render() {
	fWindow->clear();
	if(fEntity->tag() != "") {
		Vec2& position = fEntity->movement().position;
		fEntity->animation().sprite().setPosition(position.x, position.y);
		fEntity->animation().update();
		fWindow->draw(fEntity->animation().sprite());
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
	}
}

void App::setEntity() {
	if(fInterface->getEntityTag() == "") {
		return;
	}

	if (fEntity->tag() != fInterface->getEntityTag()) {
		fEntity = std::make_shared<Entity>(fAssets->getEntity(fInterface->getEntityTag()));
		fEntity->movement().position = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
		fEntity->movement().prevPosition = {WINDOW_SIZE_X/2.0f , WINDOW_SIZE_Y/2.0f};
	}
}
