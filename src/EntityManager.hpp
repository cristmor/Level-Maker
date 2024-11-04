#pragma once

// Standard
#include <array>
#include <unordered_map>
#include <memory>

// Project
#include "Animation.hpp"
#include "Entity.hpp"

class Entity;

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::unordered_map<std::string, std::vector<std::shared_ptr<Entity>>> EntityMap;

class EntityManager {
public:
	EntityManager() {}

	std::shared_ptr<Entity> addEntity(std::string tag, const sf::Vector2f& position, const sf::Vector2f& speed, const Animation& animation, short int l = 0, bool c = false);
	void deleteEntity(std::string tag, size_t id);

	const EntityVector& entities() { return mEntityVector; }
	std::shared_ptr<Entity> getEntity(size_t id);
private:
	EntityVector mEntityVector;
	EntityMap mEntityMap;
	size_t mID = 0;
};
