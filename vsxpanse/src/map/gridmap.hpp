#pragma once
#include <map>
#include <basics/vector2dint.hpp>
#include "gameobject.hpp"
#include "filesystem/resourcearchive.hpp"
#define GRIDMAPSIZE 1024
#define GRIDTILESIZE  32
/*-------------------------------------------------------
	Represents a tile in the GridMap. 
---------------------------------------------------------*/
class TileInfo
{
public:
	bool is_free()const;
	void register_agent(GameObject * obj, bool solid);
	void deregister_agent(GameObject * obj, bool solid);
private:
	void register_solid_object();
	void deregister_solid_object();
	std::vector<GameObject*> m_gameobjects;
	int m_solidness;
	const int FREE_POSITION = 0;
};

/*-------------------------------------------------------
	Contains the playable map organized in a square tile pattern
	Each position contains a MapTile
---------------------------------------------------------*/
class GridMap
{
public:
	static void initialize(ResourceArchive * archive);
	static void teardown();

	/*------------------------------------
	Move unit in grid.
	Returns true if the unit could move.
	--------------------------------------
	Returns:   bool, if the unit was able to move. false may indicate trying to move into a
	solid object.
	Parameter: GameObject * unit, unit to move.
	Parameter: const Vector2DInt & to, where to move
	Parameter: bool solid, if the unit is regarded as solid.
	------------------------------------*/
	static bool move_unit(GameObject * unit, const Vector2DInt & pixelpos_to, bool solid);

	static void register_unit(GameObject * const unit, bool solid);
	static void register_unit(GameObject * const unit, const Vector2DInt & pixelpos, bool solid);


	static TileInfo * const get_tileinfo(const Vector2DInt & gridpos);
	
	/*-------------------------------------------------------
	Gets the smallest x-position (inclusive) of the GridMap.
	---------------------------------------------------------*/
	static int get_min_x();
	/*-------------------------------------------------------

	Gets the smallest y-position (inclusive) of the GridMap.
	---------------------------------------------------------*/
	static int get_min_y();
	
	/*-------------------------------------------------------
	Gets the greatest x-position (exclusive) of the GridMap.
	---------------------------------------------------------*/
	static int get_max_x();

	/*-------------------------------------------------------
	Gets the greatest y-position (exclusive) of the GridMap.
	---------------------------------------------------------*/
	static int get_max_y();

	/*-------------------------------------------------------
	Get if the tile is currently impassable.
	---------------------------------------------------------*/
	static bool get_if_tile_is_free(const Vector2DInt & gridpos);

	/*-------------------------------------------------------
	Get if the position is within GridMap boundaries.
	---------------------------------------------------------*/
	static bool get_if_position_in_gridmap(const Vector2DInt & gridpos);
	
	/*-------------------------------------------------------
	Get size of the GridMap.
	---------------------------------------------------------*/
	static const Vector2DInt & get_size();
	
	/*-------------------------------------------------------
	PixelSpace vs GridSpace:
	
	Each tile in the grid represents a square area. 
	So if your unit is at tile (2,2) what does that translate to in
	real pixels?
		
	Here it's determined by the GRIDTILESIZE.
	If the GRIDTILESIZE is 32: 
	tile(2,2) is at PixelSpace (64, 64).
	tile(-2,-2) is at PixelSpace (-64, -64).

	Note: PixelSpace does not take into account any offset that a camera may 
	provide, so PixelSpace (64, 64) can still be outside your 1920x1080 screen, 
	if any offset is applied.

	---------------------------------------------------------*/

	/*-------------------------------------------------------
	Converts a position from PixelSpace to GridSpace.
	
	e.g. with GRIDTILESIZE = 32
	PixelSpace(0,0) = GridSpace(0,0)
	PixelSpace(1,1) = GridSpace(0,0)
	PixelSpace(31,31) = GridSpace(0,0)
	PixelSpace(32,32) = GridSpace(1,1)
	PixelSpace(-1,-1) = GridSpace(-1,-1)
	PixelSpace(-32,-32) = GridSpace(-1,-1)
	PixelSpace(-33,-33) = GridSpace(-2,-2)	
	---------------------------------------------------------*/
	static Vector2DInt pixelspace_to_gridspace(const Vector2DInt & pixelpos);
	static int pixelspace_to_gridspace(int value);


	/*-------------------------------------------------------
	Converts a position from GridSpace to PixelSpace.
	e.g. with GRIDTILESIZE = 32
	GridSpace(0,0) = PixelSpace(0,0)
	GridSpace(1,1) = PixelSpace(32,32)
	GridSpace(2,2) = PixelSpace(64,64)
	GridSpace(-1,-1) = PixelSpace(-32,-32)
	GridSpace(-2,-2) = PixelSpace(-64,-64)
	---------------------------------------------------------*/
	static Vector2DInt gridspace_to_pixelspace(const Vector2DInt & gridpos);
	static int gridspace_to_pixelspace(int value);
private:
	GridMap() {}
	static Vector2DInt m_size;
	static void generate_resources(ResourceArchive * archive);
	static bool m_initialized;
	static TileInfo *** m_objects;
};