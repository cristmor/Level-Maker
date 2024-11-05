#pragma once

// Standard
#include <memory>
#include <cstring>

// Dep
#include <SFML/Graphics.hpp>

// Project
#include "AppState.hpp"
#include "GameState.hpp"

class Assets;

class Interface {
public:
	Interface();
	~Interface();

	void update();

private:
	sf::Clock mClock;

};
