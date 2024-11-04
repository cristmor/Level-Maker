#pragma once

// Standard
#include <string>
#include <unordered_map>
#include <fstream>
#include <stdexcept>

// Deps
#include "SFML/Graphics.hpp"

// Project
#include "Animation.hpp"

class Animation;

typedef std::unordered_map<std::string, sf::Texture> TextureMap;
typedef std::unordered_map<std::string, Animation> AnimationMap;

struct AssetData {
	std::string textureTag;
	std::string animationTag;
	size_t count;
	size_t speed;
	size_t sizeX;
	size_t sizeY;
	size_t row;
	size_t column;
	bool isCustom;
	float boundingBoxX;
	float boundingBoxY;
	float offsetX;
	float offsetY;
	std::string path;
};

class Assets {
public:
	Assets();

	const Animation& getAnimation(std::string tag) { return mAnimationMap[tag]; }

private:
	void addTexture(std::string tag, std::string path);

	AnimationMap mAnimationMap;
	TextureMap mTextureMap;
};
