#include "Animation.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstddef>

Animation::Animation(std::string tag, size_t count, size_t speed, size_t sizeX, size_t sizeY, size_t row, size_t column, bool isCustom, const sf::Vector2i& offset, const sf::Vector2f& boundingBox, const sf::Texture& texture):
	mTag(tag),
	mCount(count),
	mSpeed(speed),
	mSizeX(sizeX),
	mSizeY(sizeY),
	mRow(row),
	mColumn(column),
	mCurrent(column),
	mIsCustom(isCustom),
	mOffset(offset),
	mBoundingBox({ SCALE * boundingBox.x, SCALE * boundingBox.y }),
	mSprite(texture) {

	mSprite.setOrigin((mSizeX/2.0) + mOffset.x, (mSizeY/2.0) + mOffset.y);
	mSprite.setScale(SCALE, SCALE);
	setTexture();
}

// Public
void Animation::update() {
	static size_t frames = 0;
	if(mSpeed) {
		mCurrent = (frames / (mSpeed * 6)) % mCount;
		if(mCurrent == mCount) {
			mEnded = true;
		}
		else {
			mEnded = false;
		}
	}
	setTexture();
	frames++;
}

// Private
void Animation::setTexture() {
	if(mIsCustom) {
		mSprite.setTextureRect(sf::IntRect(mRow, mColumn, mSizeX, mSizeY));
	}
	else {
		mSprite.setTextureRect(sf::IntRect(std::floor(mColumn) * mSizeX, (mRow - 1) * mSizeY, mSizeX, mSizeY));
	}
}
