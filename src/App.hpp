#pragma once

// Standard
#include <iostream>
#include <memory>
#include <fstream>

// Deps
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

// Project
#include "Interface.hpp"
#include "Assets.hpp"
#include "Entity.hpp"
#include "GameState.hpp"
#include "AppState.hpp"

const std::string OUTPUT_FILENAME = "level.txt";

class Interface;
class Assets;
class Entity;

class App {
public:
	App();
	~App();

	void run();
private:
	void render(); 
	void inputs();
	void movements();

	void setEntity();
	void setAnimation();
	void setLayer();
	void selectEntity();

	void saveLevel();
	void loadLevel();

	void setTextSetting();

	void sortEntitiesByLayer();

	
	Interface mInterface{};
	std::shared_ptr<Assets> mAssets;

	// std::vector<sf::RectangleShape> fRectangleVector;
};
