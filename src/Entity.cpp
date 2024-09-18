#include "Entity.h"

Entity::Entity() {}

Entity::Entity(const std::string& tag, const Animation& animation, const Vec2& position, const Vec2& velocity, const Vec2& size, const std::string& state):
	fTag(tag),
	fAnimation(animation),
	fMovement(position, velocity),
	fBoundingBox(size),
	fState(state) {
	fInput = Input();
}

// Public

Animation& Entity::animation() {
	return fAnimation;
}

Movement& Entity::movement() {
	return fMovement;
}

BoundingBox& Entity::boundingBox() {
	return fBoundingBox;
}

State& Entity::state() {
	return fState;
}

Input& Entity::input() {
	return fInput;
}

std::string& Entity::tag() {
	return fTag;
}

