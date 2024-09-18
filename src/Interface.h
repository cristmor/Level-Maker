#pragma once

#include "common.h"
#include "App.h"
#include "Assets.h"

class Assets;

class Interface {
public:
	Interface(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<Assets>& assets);
	~Interface();

	void whileRun();
	void render();
	void events(const sf::Event& event);

	void pathUI();
	void mousePositionUI();
	void entitySelectorUI();

	const std::string getEntityTag() const;
private:
	std::shared_ptr<sf::RenderWindow> fWindow;
	std::shared_ptr<Assets> fAssets;
	sf::Clock fClock;
	sf::Vector2i mousePosition;

	std::string fEntityTag = "";
};
