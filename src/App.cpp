#include "App.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Window/Keyboard.hpp>

App::App() {
	fAssets = std::make_shared<Assets>();
	fWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), WINDOW_TITLE);
	fInterface = std::make_shared<Interface>(fWindow, fAssets);
	fOutput.open(OUTPUT_FILENAME);

	for(int x = 0; x <= WINDOW_SIZE_X; x += (16 * SCALE)) {
		for(int y = 0; y <= WINDOW_SIZE_Y; y += (16 * SCALE)) {
			sf::RectangleShape rect;
			rect.setPosition(0, 0);
			rect.setSize({static_cast<float>(x), static_cast<float>(y)});
			rect.setFillColor({0, 0, 0, 0});
			rect.setOutlineColor(sf::Color::White);
			rect.setOutlineThickness(2);
			fRectangleVector.push_back(rect);
		}
	}

	sf::VertexArray vertices(sf::Lines);
	int RECT_SIZE = (16 * SCALE);
	for (int x = 0; x <= WINDOW_SIZE_X; x += RECT_SIZE) {
		for (int y = 0; y <= WINDOW_SIZE_Y; y += RECT_SIZE) {
			sf::Vector2f topLeft(static_cast<float>(x), static_cast<float>(y));
			sf::Vector2f bottomRight(topLeft.x + RECT_SIZE, topLeft.y + RECT_SIZE);

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

	fGrid = vertices;

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
	if(fInterface->showGrid()) {
		fWindow->draw(fGrid);
	}
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

		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::R) {
				fInterface->createEntity() = true;
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
}

void App::movements() {
	if(fInterface->followMouse()) {
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
	}
}

void App::setEntity() {
	if (fInterface->createEntity()) {
		fInterface->createEntity() = false;
		fInterface->followMouse() = true;
		fCurrentEntity = std::make_shared<Entity>(fAssets->getEntity(fInterface->getEntityTag()));
		fInterface->setAnimationTag(fCurrentEntity->animation().tag());
		fEntityVector.push_back(fCurrentEntity);
	}

	if (fInterface->deleteEntity()) {
		for (int i = 0;i < fEntityVector.size();i++) {
			if (fCurrentEntity == fEntityVector[i]) {
				fEntityVector.erase(fEntityVector.begin() + i);
			}
		}
		fCurrentEntity = fEntityVector.back();
		fInterface->setEntityTag(fCurrentEntity->tag());
		fInterface->setAnimationTag(fCurrentEntity->animation().tag());
		fInterface->deleteEntity() = false;
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
