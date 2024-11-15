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
	float x;
	float y;
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

	std::ofstream& output() { return mOutput; }

	std::string& filename() { return mFilename; }
	std::string& entityTag() { return mEntityTag; }
	std::string& animtionTag() { return mAnimationTag; }

	int& layer() { return mLayer; }
	bool& followMouse() { return mFollowMouse;}
	bool& newEntity() { return mNewEntity; }
	bool& deleteEntity() { return mDeleteEntity; }
	bool& snapGrid() { return mSnapGrid; }
	bool& showGrid() { return mShowGrid; }
	bool& save() { return mSave; }
	bool& load() { return mLoad; }

	std::vector<const char*> animationList(std::string tag);
	std::vector<const char*> textureList();

private:
	sf::Vector2i mMousePosition;
	sf::Vector2i mCameraPosition;

	std::ofstream mOutput;

	std::string mAssetPath = "/home/cristmor/dev/cpp/SpriteCapture/deps/assets/sprites/";
	std::string mFilename = "test.txt";
	std::string mEntityTag = "player";
	std::string mAnimationTag = "";

	std::vector<std::string> mAnimationList;
	std::vector<std::string> mTextureList;

	int mLayer = 1;
	bool mFollowMouse = false;
	bool mNewEntity = false;
	bool mDeleteEntity = false;
	bool mSnapGrid = false;
	bool mShowGrid = false;
	bool mSave = false;
	bool mLoad = false;
};
