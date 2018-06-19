#include "spritecomponent.hpp"


void SpriteComponent::load_sprite_from_image(ResourceFile * file)
{
	if (m_sprite != nullptr)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}
	SDL_Texture * text = GraphicsManager::load_texture(file);
	m_sprite = new Sprite(text);
}

void SpriteComponent::load_sprite_from_image(ResourceFile * file, const Rect & rect)
{
	if (m_sprite != nullptr)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}
	SDL_Texture * text = GraphicsManager::load_texture(file);
	m_sprite = new Sprite(text, rect.get_sdl_rect());
}

SpriteComponent::~SpriteComponent()
{
	if (m_sprite != nullptr)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}
}
void SpriteComponent::render() {
	if (m_sprite)
	{
		GraphicsManager::render_texture(
			*m_sprite,
			Vector2D(m_owner->transform().get_position()),
			m_owner->transform().get_scale(),
			m_owner->transform().get_rotation().z,
			m_centered,
			m_flip
		);
	}
}