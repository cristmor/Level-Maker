#pragma once
#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"
#include "Entity.h"

class Entity;

typedef std::shared_ptr<sf::RenderWindow> SharedWindow;
typedef std::shared_ptr<Entity> SharedEntity;
typedef std::vector<SharedEntity> EntityVector;

const float WINDOW_SIZE_X = 1280;
const float WINDOW_SIZE_Y = 1280;
const float SCALE = 3.0f;
const std::string WINDOW_TITLE = "Level Maker";
const std::string OUTPUT_FILENAME = "";

class EditorState {
public:
	EntityVector entities;
	SharedEntity currentEntity;
	SharedWindow window;
};
