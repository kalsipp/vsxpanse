#include "textcomponent.hpp"
#include <SDL_ttf.h>

TextComponent::TextComponent(GameObject * owner): Component(owner), m_sprite(nullptr) {
}

TextComponent::~TextComponent() {
	if (m_font != nullptr) TTF_CloseFont((TTF_Font*)m_font);
}

void TextComponent::initialize(ResourceFile * file, int size)
{
	m_font_source = file;
	m_font = (TTF_Font*)m_font_source->get_font(size);
}

void TextComponent::set_font_size(int size) {
	if (m_font != nullptr) TTF_CloseFont((TTF_Font*)m_font);
	m_font = (TTF_Font*)m_font_source->get_font(size);
	ASSERT(m_font, "Could not load font ");
	set_text(m_text);
}

std::string TextComponent::get_text() {
	return m_text;
}

void TextComponent::set_text(const std::string & text) {
	m_text = text;
	if (m_sprite->get_sdl_texture() != nullptr)
	{
		GraphicsManager::destroy_texture(m_sprite->get_sdl_texture());
	}
	RectInt color = {255, 255, 255, 1};
	m_sprite = GraphicsManager::get_sprite_from_text(m_text, m_font, color);
	ASSERT(m_sprite->get_sdl_texture(), "Could not set text " + std::string(SDL_GetError()));
}

void TextComponent::render() {
	//ASSERT(m_sprite.get_sdl_texture(), "This is apparently zero now");
	if (m_sprite->get_sdl_texture() == nullptr) return;
	GraphicsManager::render_texture(
	    *m_sprite,
	    Vector2D(m_owner->transform().get_position()),
	    m_scale,
	    m_angle,
	    m_centered
	);
}