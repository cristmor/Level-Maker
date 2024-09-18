#pragma once

#include "common.h"

const Vec2 fScale = {3.0f, 3.0f};

class Animation {
public:
	Animation();
	Animation(const std::string& tag, const sf::Texture& t);
	Animation(const std::string& tag, const sf::Texture& t, const unsigned int& count, const unsigned int& s);
	Animation(const std::string& tag, const sf::Texture& texture, const unsigned int& count, const unsigned int& speed, const unsigned int& size, const unsigned int& position, const Vec2& centerOffset = {0.0f, 0.0f});

	void update();

	const bool& hasEnded() const;
	const std::string& tag() const;
	const Vec2& getSize() const;
	sf::Sprite& sprite();

private:

	sf::Sprite fSprite;
	unsigned int fCellCount = 0;
	unsigned int fCurrentFrame = 0;
	unsigned int fSpeed = 0;
	unsigned int fPosition = 1;
	std::string fTag = "";
	Vec2 fSize = {1, 1};
	bool fEnded = false;
};

