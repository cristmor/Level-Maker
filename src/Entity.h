#pragma once

#include "common.h"
#include "Component.h"
#include "Animation.h"

class Entity {
public:
	Entity();
	Entity(const std::string& tag, const Animation& animation, const Vec2& position, const Vec2& velocity, const Vec2& size, const std::string& state);
	
	Animation& animation();
	Movement& movement();
	BoundingBox& boundingBox();
	Input& input();
	State& state();
	std::string& tag();

private:

	Animation fAnimation;
	Movement fMovement;
	BoundingBox fBoundingBox;
	Input fInput;
	State fState;

	std::string fTag = "";
};
