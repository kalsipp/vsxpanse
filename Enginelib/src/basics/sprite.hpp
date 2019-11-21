#pragma once
#include <string>
#include "vector2d.hpp"
#include "helpers.hpp"
#include "rectint.hpp"

struct SDL_Texture;
class Sprite {
public:
	Sprite(SDL_Texture * new_text);
	Sprite(SDL_Texture * new_text, const RectInt &);
	~Sprite(){}
	SDL_Texture * get_sdl_texture()const;
	const RectInt & get_rect()const;
private:
	SDL_Texture * m_texture = nullptr;
	RectInt m_rect; 
};