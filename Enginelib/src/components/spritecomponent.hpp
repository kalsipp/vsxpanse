#pragma once
#include <SDL.h>
#include <SDL_image.h>
//#include "../resources/engine_resource_paths.hpp"
#include "../component.hpp"
#include "../basics/sprite.hpp"
#include "../basics/vector2d.hpp"
#include "../basics/helpers.hpp"
#include "../gameobject.hpp"
#include "../graphicsmanager.hpp"
#include "../basics/rect.hpp"


class SpriteComponent: public Component {
public:
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

