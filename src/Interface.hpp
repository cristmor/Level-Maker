#pragma once

// Standard
#include <memory>
#include <cstring>

// Dep
#include <SFML/Graphics.hpp>

// Project
#include "AppState.hpp"
#include "GameState.hpp"
#include "Assets.hpp"

class Assets;

class Interface {
public:
	Interface();

	void whileRun();
	void render();
	void events(const sf::Event& event);

	void pathUI();
	void mousePositionUI();
	void entitySelectorUI();
	void animationSelectorUI();
	void moveEntityUI();
	void saveUI();

private:
	sf::Clock mClock;

};
