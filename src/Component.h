#pragma once

#include "common.h"
#include "Animation.h"

const unsigned int texSizeX = 200;
const unsigned int texSizeY = 200;

class Component {
public:
	bool has = false;
};

class Movement: public Component {
public:
	Movement() { has = true; }
	Movement(const Vec2& p): position(p), prevPosition(p) { has = true; }
	Movement(const Vec2& p, const Vec2& v): position(p), prevPosition(p), velocity(v) { has = true; }
	~Movement() {}

	Vec2 position = { 0.0f, 0.0f };
	Vec2 prevPosition = { 0.0f, 0.0f };
	Vec2 velocity = { 0.0f, 0.0f };
};

class BoundingBox: public Component {
public:
	BoundingBox() { has = true; }
	BoundingBox(const Vec2& s): size(Vec2(s.x*fScale.x, s.y*fScale.y)), halfSize(Vec2((s.x*fScale.x)/2 , (s.y*fScale.y)/2)) { has = true; }
	~BoundingBox() {}

	Vec2 size;
	Vec2 halfSize;
};


class Input: public Component {
public:
	Input() { has = true; }
	~Input() { has = true; }
	
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	bool attack = false;
};

class State: public Component {
public:
	State() { has = true; }
	State(const std::string& s): state(s) { has = true; }
	~State() {}

	std::string state;
};
