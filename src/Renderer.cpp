#include "Renderer.hpp"
#include "GameState.hpp"
#include <SFML/Window/Event.hpp>

// Public
void Renderer::render() {
	auto& window = GameState::getInstance().window();

	window.clear();
	for(auto& entity : GameState::getInstance().entityManager().entities()) {
		if(entity) {
			entity->update();
			window.draw(entity->sprite());
		}
	}
	window.display();
}
