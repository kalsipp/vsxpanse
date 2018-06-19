#pragma once
#include <map>
#include <basics/vector2dint.hpp>
#include "maptile.hpp"
#include "gameobject.hpp"
#include "basics/sprite.hpp"
#include "filesystem/resourcearchive.hpp"

/*-------------------------------------------------------
	Generates and contains the map background
---------------------------------------------------------*/
class GridBackground : public Component
{
public:
	GridBackground() {}
	void initialize(const Vector2DInt & size, ResourceArchive * archive);
	void render()override;
	void teardown()override;
private:
	void generate_resources(ResourceArchive * archive);
	Sprite * m_map_sprite = nullptr;

	/*-------------------------------------------------------
	Note that this texture is owned by the GridBackground
	---------------------------------------------------------*/
	SDL_Texture * m_texture;
	void generate_surface(ResourceArchive * archive);
	Vector2DInt m_size;
	std::map<Vector2DInt, MapTile*> m_tiles;
};