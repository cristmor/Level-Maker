#include "Animation.h"

Animation::Animation() {
}

Animation::Animation(const std::string& tag, const sf::Texture& t):
	Animation(tag, t, 1, 0) {
}

Animation::Animation(const std::string& tag, const sf::Texture& t, const unsigned int& count, const unsigned int& s):
	fTag(tag),
	fSprite(t),
	fCellCount(count),
	fSpeed(s) {
}

Animation::Animation(const std::string& tag, const sf::Texture& texture, const unsigned int& count, const unsigned int& speed, const unsigned int& size, const unsigned int& position, const Vec2& centerOffset):
	fTag(tag),
	fSprite(texture),
	fCellCount(count),
	fSpeed(speed),
	fSize(Vec2(size, size)),
	fPosition(position) {
	fSprite.setOrigin((fSize.x/2) + centerOffset.x, (fSize.y/2) + centerOffset.y);
	fSprite.setScale(fScale.x, fScale.y);
}

// Public
void Animation::update() {
	unsigned int currentCell = 0;
	if(fSpeed) {
		currentCell = (fCurrentFrame/fSpeed) % fCellCount;
	}
	fSprite.setTextureRect(sf::IntRect(std::floor(currentCell)*fSize.x, fSize.y*(fPosition - 1), fSize.x, fSize.y));
	if(currentCell == fCellCount-1) {
		fEnded = true;
	}
	else {
		fEnded = false;
	}
	fCurrentFrame++;
}

const bool& Animation::hasEnded() const {
	return fEnded;
}

const std::string& Animation::tag() const {
	return fTag;
}

const Vec2& Animation::getSize() const {
	return fSize;
}

sf::Sprite& Animation::sprite() {
	return fSprite;
}

// Private

