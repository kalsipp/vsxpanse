#pragma once
#include "../component.hpp"

class ResourceFile;
class Rect;
class Sprite;
class GameObject;
class SpriteComponent: public Component {
public:
	SpriteComponent(GameObject * owner):Component(owner) {}
	void load_sprite_from_image(ResourceFile * file);
	void render() final override;
private:
	std::unique_ptr<Sprite> m_sprite = nullptr;
	double m_angle = 0;
	bool m_centered = false;
};

