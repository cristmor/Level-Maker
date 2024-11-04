#include "Entity.hpp"

Entity::Entity(std::string tag, size_t id, const sf::Vector2f& position, const sf::Vector2f& speed, const Animation& animation, short int l, bool c):
	mTag(tag),
	mID(id),
	mPosition(position),
	mPrevPosition(position),
	mSpeed(speed),
	mAnimation(animation),
	layer(l),
	collidable(c) {
	update();
}

// Public
void Entity::update() {
	mAnimation.update();
	mAnimation.setPosition(mPosition);
}

void Entity::setPosition(const sf::Vector2f& newPosition) {
	mPrevPosition = mPosition;
	mPosition = newPosition;
}
