#pragma once

// Standard
#include <fstream>
#include <memory>
#include <string>

// Deps
#include <SFML/Graphics.hpp>

// Project
#include <Entity.hpp>

struct Output {
	int x;
	int y;
	std::string eTag;
	std::string aTag;
	int layer;
};

class AppState {
public:
	AppState() {}

	static AppState& getInstance() {
		static AppState instance;
		return instance;
	}

	AppState(const AppState&) = delete;
	AppState& operator = (const AppState&) = delete;

	sf::Vector2i& mousePosition() { return mMousePosition; }
	sf::Vector2i& cameraPosition() { return mCameraPosition; }
	sf::VertexArray& grid() { return mGrid; }
	sf::Text& textPosition() { return mTextPosition; }
	sf::Font& font() { return mFont; }
	std::ofstream& output() { return mOutput; }
	int& layer() { return mLayer; }
	bool& followMouse() { return mFollowMouse;}
	bool& newEntity() { return mNewEntity; }
	bool& deleteEntity() { return mDeleteEntity; }
	bool& snapGrid() { return mSnapGrid; }
	bool& showGrid() { return mShowGrid; }
	bool& save() { return mSave; }
	bool& load() { return mLoad; }
	std::string& filename() { return mFilename; }
	std::string& entityTag() { return mEntityTag; }
	std::string& animtionTag() { return mAnimationoTag; }
	std::shared_ptr<Entity>& currentEntity() { return mCurrentEntity; }

private:
	sf::Vector2i mMousePosition;
	sf::Vector2i mCameraPosition;
	sf::VertexArray mGrid;
	sf::Text mTextPosition;
	sf::Font mFont;
	std::ofstream mOutput;
	int mLayer = 1;
	bool mFollowMouse;
	bool mNewEntity;
	bool mDeleteEntity;
	bool mSnapGrid;
	bool mShowGrid;
	bool mSave;
	bool mLoad;
	std::string mFilename = "test.txt";
	std::string mEntityTag = "";
	std::string mAnimationoTag = "";
	std::shared_ptr<Entity> mCurrentEntity;
};
