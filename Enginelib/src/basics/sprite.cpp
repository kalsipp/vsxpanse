#include "sprite.hpp"
#include <SDL.h>

Sprite::Sprite(SDL_Texture * new_text): m_texture(new_text) {
	int width = 0;
	int height = 0;
	SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);
	m_rect = {0, 0, width, height};
}

Sprite::Sprite(SDL_Texture * new_text, const RectInt & new_rect):
	m_texture(new_text),
	m_rect(new_rect) {}


SDL_Texture * Sprite::get_sdl_texture()const {
	return m_texture;
}

const RectInt & Sprite::get_rect() const {
	return m_rect;
}
