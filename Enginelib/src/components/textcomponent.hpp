#pragma once
#include <string>
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
	void render() final override;
private:
	std::string m_text = "";
	std::unique_ptr<Sprite> m_sprite;
	void * m_font = nullptr; //TTF_Font
	ResourceFile * m_font_source;
	Vector2D m_scale = {1, 1};
	double m_angle = 0;
	bool m_centered = false;
	const int default_font_size = 16;
	const std::string m_default_font = "";
};