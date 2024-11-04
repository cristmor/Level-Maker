#pragma once

// Standard
#include <SFML/System/Vector2.hpp>
#include <memory_resource>
#include <string>

// Deps
#include "SFML/Graphics.hpp"

// Project
#include "Animation.hpp"

class Animation;

struct Input {
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	bool attack = false;
};

class Entity {
public:
	Entity() {}
	Entity(std::string tag, size_t id, const sf::Vector2f& position, const sf::Vector2f& speed, const Animation& Animation, short int l = 0, bool c = false);

	void update();
	void setPosition(const sf::Vector2f& newPosition);
	void setAnimation(const Animation& animation) { mAnimation = animation; }

	const sf::Vector2f& position() const { return mPosition; }
	const sf::Vector2f& prevPosition() const { return mPrevPosition; }
	const sf::Vector2f& speed() const { return mSpeed; }
	const std::string& tag() const { return mTag; }
	const size_t& copyNo() const { return mID; }

	const sf::Vector2f boundingBox() const { return mAnimation.boundingBox(); }
	sf::Sprite& sprite() { return mAnimation.sprite(); }
	const size_t& size() const { return mAnimation.size(); }
	const std::string& animationTag() const { return mAnimation.tag(); }

	std::string state = "idle";
	std::string prevState = "down";
	Input input;

	short int layer = 0;
	bool collidable = false;

private:
	Animation mAnimation;
	std::string mTag;
	sf::Vector2f mPosition = {0,0};
	sf::Vector2f mPrevPosition = {0,0};
	sf::Vector2f mSpeed = {0,0};
	size_t mID = 0;
};
