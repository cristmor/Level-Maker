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
	void animationSelectorUI();
	void moveEntityUI();

	const std::string getEntityTag() const;
	const std::string getAnimation() const;
	bool& followMouse();
	bool& createEntity();

	void setEntityTag(const std::string& tag);
	void setAnimationTag(const std::string& tag);
private:
	std::shared_ptr<sf::RenderWindow> fWindow;
	std::shared_ptr<Assets> fAssets;
	sf::Clock fClock;
	sf::Vector2i mousePosition;

	std::string fEntityTag = "";
	std::string fAnimationTag = "";
	bool fCreateEntity = false;
	bool fFollowMouse = false;
};
