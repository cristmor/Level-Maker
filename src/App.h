#pragma once

#include "common.h"
#include "Interface.h"
#include "Assets.h"
#include "Entity.h"

const float WINDOW_SIZE_X = 1280;
const float WINDOW_SIZE_Y = 720;
const std::string WINDOW_TITLE = "Level Maker";
const float SCALE = 3.0f;
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

	void setTextSetting();

	void sortEntitiesByLayer();

	std::shared_ptr<sf::RenderWindow> fWindow;
	std::shared_ptr<Interface> fInterface;
	std::shared_ptr<Assets> fAssets;
	std::ofstream fOutput;

	std::vector<std::shared_ptr<Entity>> fEntityVector;
	std::vector<sf::RectangleShape> fRectangleVector;
	std::shared_ptr<Entity> fCurrentEntity;
	sf::Vector2i fMousePosition;
	sf::VertexArray fGrid;
	sf::Text fTextPosition;
	sf::Font fFont;
};
