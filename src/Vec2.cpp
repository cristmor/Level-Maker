#include "Vec2.h"

Vec2::Vec2() {
}

Vec2::Vec2(const float& fx, const float& fy):
	x(fx),
	y(fy) {
}

Vec2::~Vec2() {
}

// Public
bool Vec2::operator == (const Vec2& vec) {
	return (x == vec.x && y == vec.y);
}

bool Vec2::operator != (const Vec2& vec) {
	return (x != vec.x && y != vec.y);
}

Vec2 Vec2::operator + (const Vec2& vec) {
	return Vec2(x + vec.x, x + vec.y);
}

Vec2 Vec2::operator - (const Vec2& vec) {
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator * (const float& value) {
	return Vec2(x*value, y*value);
}

Vec2 Vec2::operator / (const float& value) {
	return Vec2(x/value, y/value);
}

void Vec2::operator += (const Vec2& vec) {
	x += vec.x;
	y += vec.y;
}

void Vec2::operator -= (const Vec2& vec) {
	x -= vec.x;
	y -= vec.y;
}

void Vec2::operator *= (const float& value) {
	x *= value;
	y *= value;
}

void Vec2::operator /= (const float& value) {
	x /= value;
	y /= value;
}
