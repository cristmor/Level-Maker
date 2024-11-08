#pragma once

// Standard
#include <fstream>
#include <memory>
#include <string>
#include <filesystem>

// Deps
#include <SFML/Graphics.hpp>

// Project
#include "GameState.hpp"
#include "Entity.hpp"

struct Output {
	int x;
	int y;
	std::string eTag;
	std::string aTag;
	int layer;
};

class AppState {
public:
	AppState();

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

	std::vector<const char*>& filenamesChar() { return mFilenamesChar;}
	std::string& filename() { return mFilename; }
	std::string& entityTag() { return mEntityTag; }
	std::string& animtionTag() { return mAnimationTag; }
	std::shared_ptr<Entity>& currentEntity() { return mCurrentEntity; }

	int& layer() { return mLayer; }
	bool& followMouse() { return mFollowMouse;}
	bool& newEntity() { return mNewEntity; }
	bool& deleteEntity() { return mDeleteEntity; }
	bool& snapGrid() { return mSnapGrid; }
	bool& showGrid() { return mShowGrid; }
	bool& save() { return mSave; }
	bool& load() { return mLoad; }

	std::vector<const char*> animationList(std::string tag);

private:
	sf::Vector2i mMousePosition;
	sf::Vector2i mCameraPosition;
	sf::VertexArray mGrid;
	sf::Text mTextPosition;
	sf::Font mFont;

	std::ofstream mOutput;
	std::vector<std::filesystem::path> mPaths;
	std::vector<std::string> mFilenames;
	std::vector<const char*> mFilenamesChar;

	std::string mAssetPath = "/home/cristmor/dev/cpp/SpriteCapture/deps/assets/sprites/";
	std::string mFilename = "test.txt";
	std::string mEntityTag = "player";
	std::vector<std::string> mAnimationList;
	std::string mAnimationTag = "";
	std::shared_ptr<Entity> mCurrentEntity;

	int mLayer = 1;
	bool mFollowMouse = false;
	bool mNewEntity = false;
	bool mDeleteEntity = false;
	bool mSnapGrid = false;
	bool mShowGrid = false;
	bool mSave = false;
	bool mLoad = false;
};
