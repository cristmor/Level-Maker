#include "EntityManager.hpp"
#include <memory>

// public
std::shared_ptr<Entity> EntityManager::addEntity(std::string tag ,const sf::Vector2f& position, const sf::Vector2f& speed, const Animation& animation, short int l, bool c) {
	std::shared_ptr<Entity> entity = std::make_shared<Entity>(tag, mID, position, speed, animation, l, c);
	mEntityVector.push_back(entity);
	mEntityMap[tag].push_back(entity);
	mID++;

	return entity;
}

void EntityManager::deleteEntity(std::string tag, size_t id) {
	mEntityVector[id] = nullptr;

	/*
	if(mEntityMap.find(tag) != mEntityMap.end()) {
		for(size_t i = 0;i < mEntityMap[tag].size();i++) {
			if(mEntityMap[tag][i]->copyNo() == id) {
				mEntityMap[tag].erase(mEntityMap[tag].begin() + i);
			}
		}
	}
	*/

}

std::shared_ptr<Entity> EntityManager::getEntity(size_t id) {
	return mEntityVector[id];
}


