#pragma once

// Standard
#include <SFML/System/Vector2.hpp>
#include <string>
#include <cmath>

// Deps
#include "SFML/Graphics.hpp"

const float SCALE = 3.0f;

class Animation{
public:
	Animation() {}
	Animation(std::string tag, size_t count, size_t speed, size_t sizeX, size_t sizeY, size_t row, size_t column, bool isCustom, const sf::Vector2i& offset, const sf::Vector2f& boundingBox, const sf::Texture& texture);

	void update();

	const std::string& tag() const { return mTag; }

	short int layer = 0;

private:
	friend class Entity;

	void setTexture();

	void setPosition(const sf::Vector2f& position) { mSprite.setPosition(position); }
	const sf::Vector2f& boundingBox() const { return mBoundingBox; }
	sf::Sprite& sprite() { return mSprite; }
	const size_t& size() const { return mSizeX;}

	sf::Sprite mSprite;
	std::string mTag;
	sf::Vector2i mOffset = {0,0};
	sf::Vector2f mBoundingBox = {0,0};
	size_t mCount = 0;
	size_t mCurrent = 0;
	size_t mSpeed = 0;
	size_t mRow = 0;
	size_t mColumn = 0;
	size_t mSizeX = 0;
	size_t mSizeY = 0;
	bool mIsCustom = false;
	bool mEnded = false;
};
