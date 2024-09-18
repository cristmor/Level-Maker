#pragma once

#include "common.h"
#include "Entity.h"
#include "Animation.h"

const std::string basePath = "/home/cristmor/dev/cpp/GLGame/deps/assets/sprites/";

struct Data{
	std::string textureTag;
	std::string animationTag;
	int frameCount;
	int frameSpeed;
	int frameSize;
	int frameRow;
	Vec2 bbSize;
	Vec2 bbOffset;
	std::string texturePath;
};

class Assets {
public:
	Assets();
	~Assets();

	const sf::Texture& getTexture(const std::string& tag);
	const Animation& getAnimation(const std::string& tag);
	const Entity& getEntity(const std::string& tag);
	const std::vector<std::string> listEntityTags();

private:
	void addTexture(const std::string& tag, const std::string& path);
	void addAnimation(const std::string& tag, const sf::Texture& texture, const unsigned int& count, const unsigned int& speed, const unsigned int& size, const unsigned int& position, const Vec2& centerOffset = {0.0f, 0.0f});
	void addEntity(const std::string& tag, const Animation& animation, const Vec2& position, const Vec2& velocity, const Vec2& size, const std::string& state);

	std::unordered_map<std::string, Entity> fEntityMap;
	std::unordered_map<std::string, Animation> fAnimationMap;
	std::unordered_map<std::string, sf::Texture> fTextureMap;
};
