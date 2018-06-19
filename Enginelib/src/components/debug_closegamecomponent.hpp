#pragma once
#include "../engine.hpp"
#include "../inputmanager.hpp"

struct Debug_CloseGameComponent : public Component {
	inline void update() final override {
		if (InputManager::get_key_down(INPUT_KEY_QUIT) ||
		        InputManager::get_key_down(SDL_SCANCODE_Q)) {
			Engine::stop();
		}
	}
};