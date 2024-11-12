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
#include "Renderer.hpp"
#include "Interface.hpp"
#include "GameState.hpp"
#include "AppState.hpp"

const std::string OUTPUT_FILENAME = "level.txt";

class Interface;
class Renderer;

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
	void selectEntity();

	void saveLevel();
	void loadLevel();

	void setTextSetting();

	void sortEntitiesByLayer();

	
	Interface mInterface{};

	Renderer mRenderer{};
	// std::vector<sf::RectangleShape> fRectangleVector;
};
