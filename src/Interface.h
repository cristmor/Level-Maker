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
	void saveUI();

	const std::string getEntityTag() const;
	const std::string getAnimation() const;
	const std::string getFilename() const;
	int& layer();
	bool& followMouse();
	bool& snapGrid();
	bool& showGrid();
	bool& createEntity();
	bool& deleteEntity();
	bool& save();

	void setEntityTag(const std::string& tag);
	void setAnimationTag(const std::string& tag);
	void setLayer(const int& layer);
private:
	std::shared_ptr<sf::RenderWindow> fWindow;
	std::shared_ptr<Assets> fAssets;
	sf::Clock fClock;
	sf::Vector2i mousePosition;

	std::string fFilename = "level.txt";
	std::string fEntityTag = "";
	std::string fAnimationTag = "";
	int fLayer = 1;
	bool fCreateEntity = false;
	bool fDeleteEntity = false;
	bool fFollowMouse = false;
	bool fSnapGrid = false;
	bool fShowGrid = false;
	bool fSave = false;
};
