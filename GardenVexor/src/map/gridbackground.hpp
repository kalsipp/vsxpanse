#pragma once
#include <map>
#include <basics/vector2dint.hpp>
#include "gameobject.hpp"
#include "basics/sprite.hpp"
#include "filesystem/resourcearchive.hpp"
#include "gridmap.hpp"
#define SDL_SURFACE_MAX_SIZE 8192
#if ((GRIDMAPSIZE*GRIDTILESIZE)%SDL_SURFACE_MAX_SIZE != 0)
#error GRIDMAPSIZE*GRIDTILESIZE has to be divisible with 8192
#endif
#define GRIBACKGROUND_NUMBER_OF_PARTS_X (GRIDMAPSIZE*GRIDTILESIZE) / (SDL_SURFACE_MAX_SIZE)
#define GRIBACKGROUND_NUMBER_OF_PARTS GRIBACKGROUND_NUMBER_OF_PARTS_X*GRIBACKGROUND_NUMBER_OF_PARTS_X

/* Not used as it uses like 5gb of ram,
	Need to figure out another way of randomly generating environments
*/

/*-------------------------------------------------------
Represents an environment tile in the playable map.
---------------------------------------------------------*/
struct MapTile
{
	/*-------------------------------------------------------
	Defines paths to files, each tile has an enum which
	represents a path.
	---------------------------------------------------------*/
	const enum MapTileSprite
	{
		BASIC_GROUND,
		GRASS,
		SIZEOF_MAPTILESPRITE
	};

	static const std::string MapTilePaths[SIZEOF_MAPTILESPRITE];

	/*-------------------------------------------------------
	---------------------------------------------------------*/
	MapTile(const MapTileSprite sprite);

	/*-------------------------------------------------------
	Which sprite is used by this tile
	---------------------------------------------------------*/
	const MapTileSprite m_sprite;

};


/*-------------------------------------------------------
	Generates and contains the map background
---------------------------------------------------------*/
class GridBackground : public Component
{
public:
	GridBackground(GameObject * owner) :Component(owner) {}
	void initialize(ResourceArchive * archive);
	void render()override;
	void teardown()override;
private:
	Sprite * m_map_sprite = nullptr;
	Sprite *m_map_sprites[GRIBACKGROUND_NUMBER_OF_PARTS];

	/*-------------------------------------------------------
	Note that this texture is owned by the GridBackground
	---------------------------------------------------------*/
	//SDL_Texture * m_texture;
	void generate_surface(ResourceArchive * archive);
	Vector2DInt m_size;
	SDL_Texture *m_textures[GRIBACKGROUND_NUMBER_OF_PARTS];
};