#include "Assets.h"

Assets::Assets() {
	std::ifstream file("/home/cristmor/dev/cpp/SpriteCapture/Output.txt");

	Data data;

	std::string prevTextureTag;

	while(file.good()) {
		file >> data.textureTag
			>> data.animationTag
			>> data.frameCount
			>> data.frameSpeed
			>> data.frameSize
			>> data.frameRow
			>> data.bbSize.x
			>> data.bbSize.y
			>> data.bbOffset.x
			>> data.bbOffset.y
			>> data.texturePath;

		addTexture(data.textureTag, data.texturePath);
		addAnimation(data.animationTag, fTextureMap[data.textureTag], data.frameCount, data.frameSpeed, data.frameSize, data.frameRow, {data.bbOffset.x, data.bbOffset.y});

		if(prevTextureTag != data.textureTag) {
			addEntity(data.textureTag, fAnimationMap[data.animationTag], {0.0f, 0.0f}, {0.5f, 0.5f}, {data.bbSize.x, data.bbSize.y}, "idle");
		}
		prevTextureTag = data.textureTag;

	}
	
	file.close();

	// Load Textures
	/*
	addTexture("player", "characters/player.png");

	// Load Animations
	addAnimation("player_i_down", fTextureMap["player"], 6, 90, 48, 1, {0.0f, 8.0f});

	// Load Entity
	std::string tag = "player";
	addEntity(tag, fAnimationMap["player_i_down"], {0.0f, 0.0f}, {0.5f, 0.5f}, {15.0f, 20.0f}, "idle");
	*/
	
}

Assets::~Assets() {
}

// Public
const sf::Texture& Assets::getTexture(const std::string& tag) {
	return fTextureMap[tag];
}

const Animation& Assets::getAnimation(const std::string& tag) {
	return fAnimationMap[tag];
}

const Entity& Assets::getEntity(const std::string& tag) {
	return fEntityMap[tag];
}

const std::vector<std::string> Assets::listEntityTags() {
	std::vector<std::string> out;
	for(const auto& pair: fEntityMap) {
		auto entity = pair.second;
		out.push_back(entity.tag());
	}

	std::sort(out.begin(), out.end());

	return out;
}

const std::vector<std::string> Assets::listAnimationTags(const std::string& entityTag) {
	std::vector<std::string> out;
	if (entityTag == "") {
		std::cout << "empty" << std::endl;
		return out;
	}
	for(auto& pair: fAnimationMap) {
		if(pair.second.tag().substr(0, entityTag.size() - 1) == entityTag.substr(0, entityTag.size() - 1)) {
			out.push_back(pair.second.tag());
		}
	}

	std::sort(out.begin(), out.end());

	return out;
}

// Private
void Assets::addTexture(const std::string& tag, const std::string& path) {
	if(fTextureMap.find(tag) != fTextureMap.end()) {
		return;
	}
	else if(!fTextureMap[tag].loadFromFile(path)) {
		std::cout << "Error: Unable to load " + path << std::endl;
	}
}

void Assets::addAnimation(const std::string& tag, const sf::Texture& texture, const unsigned int& count, const unsigned int&speed, const unsigned int& size, const unsigned int& position, const Vec2& centerOffset) {
	fAnimationMap[tag] = Animation(tag, texture, count, speed, size, position, centerOffset);
}

void Assets::addEntity(const std::string& tag, const Animation& animation, const Vec2& position, const Vec2& velocity, const Vec2& size, const std::string& state) {
	if(fEntityMap.find(tag) != fEntityMap.end()) {
		return;
	}
	else {
		fEntityMap[tag] = Entity(tag, animation, position, velocity, size, state);
	}
}

