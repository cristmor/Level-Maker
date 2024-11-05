#pragma once

// Project
#include "Assets.hpp"
#include "EntityManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

const size_t WINDOW_SIZE_X = 1280;
const size_t WINDOW_SIZE_Y = 720;
const std::string WINDOW_TITLE = "Level Maker";

class GameState {
public:
	GameState();

	static GameState& getInstance() {
		static GameState instance;
		return instance;
	}

	GameState(const GameState&) = delete;
	GameState& operator = (const GameState&) = delete;

	sf::RenderWindow& window() { return mWindow;}
	Assets& assets() { return mAssets; }
	EntityManager& entityManager() { return mEntityManager; }

private:
	sf::RenderWindow mWindow{sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close};
	Assets mAssets;
	EntityManager mEntityManager;

};
