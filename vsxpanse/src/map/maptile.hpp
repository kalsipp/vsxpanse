#pragma once
#include <string>


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
	MapTile(MapTileSprite sprite);
	
	/*-------------------------------------------------------
		Which sprite is used by this tile
	---------------------------------------------------------*/
	MapTileSprite m_sprite;

};