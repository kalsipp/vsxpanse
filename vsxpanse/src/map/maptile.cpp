#include "maptile.hpp"

MapTile::MapTile(MapTileSprite sprite) :m_sprite(sprite) {}

const std::string MapTile::MapTilePaths[SIZEOF_MAPTILESPRITE] = {
	"Images\\ground.png",
	"Images\\grass.png"
};