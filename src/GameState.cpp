#include "GameState.hpp"

GameState::GameState() {
	mWindow.setFramerateLimit(60);
	mAssets = Assets();
	mEntityManager = EntityManager();
}
