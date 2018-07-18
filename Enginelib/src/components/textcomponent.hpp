#pragma once
#include <string>
#include <SDL_ttf.h>
#include <cstdint>
#include "../basics/sprite.hpp"
#include "../basics/vector2d.hpp"
#include "../graphicsmanager.hpp"
#include "../gameobject.hpp"
#include "../filesystem/resourcearchive.hpp"
#include "../basics/helpers.hpp"

class TextComponent : public Component {
public:
	TextComponent(GameObject *);
	~TextComponent();
	void initialize(ResourceFile * file, int size = 16);
	void set_font_size(int);
	std::string get_text();
	void set_text(const std::string &);
	void set_color(uint8_t, uint8_t, uint8_t, uint8_t = 0);
	void render() final override;
private:
	std::string m_text = "";
	Sprite m_sprite;
	TTF_Font * m_font = nullptr;
	ResourceFile * m_font_source;
	Vector2D m_scale = {1, 1};
	double m_angle = 0;
	bool m_centered = false;
	SDL_RendererFlip m_flip = SDL_FLIP_NONE;
	SDL_Color m_color = {255, 255, 255, 1};
	const int default_font_size = 16;
	const std::string m_default_font = "";
};