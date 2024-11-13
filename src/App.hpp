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
	void selectEntity();
	void sortEntitiesByLayer();
	
	Interface mInterface{};
	Renderer mRenderer{};

	sf::VertexArray mGrid;
	std::shared_ptr<Entity> mCurrentEntity;
	sf::Font mFont;
	sf::Text mTextPosition;

	// std::vector<sf::RectangleShape> fRectangleVector;
};
