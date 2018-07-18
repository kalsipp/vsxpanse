#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../component.hpp"

class ResourceFile;
class Rect;
class Sprite;
class GameObject;
class SpriteComponent: public Component {
public:
	SpriteComponent(GameObject * owner):Component(owner) {}
	~SpriteComponent();
	void load_sprite_from_image(ResourceFile * file);
	void load_sprite_from_image(ResourceFile * file, const Rect &);
	void render() final override;
private:
	Sprite * m_sprite = nullptr;
	double m_angle = 0;
	bool m_centered = false;
	SDL_RendererFlip m_flip = SDL_FLIP_NONE;
};

