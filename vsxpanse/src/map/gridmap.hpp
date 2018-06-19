#pragma once
#include <map>
#include <basics/vector2dint.hpp>
#include "gameobject.hpp"
#include "filesystem/resourcearchive.hpp"
/*-------------------------------------------------------
	Contains the playable map organized in a square tile pattern
	Each position contains a MapTile
---------------------------------------------------------*/
class GridMap
{
public:
	static void initialize(const Vector2DInt & size, ResourceArchive * archive);
	static void teardown();
	
	/*-------------------------------------------------------
		Moved unit in grid.
		Returns true if the unit could move.
	---------------------------------------------------------*/
	static bool move_unit(GameObject * unit, const Vector2DInt & from, const Vector2DInt & to);

	static std::vector<GameObject*>* get_objects_at_position(const Vector2DInt & pos);

private:
	GridMap() {}
	static Vector2DInt m_size;
	static void add_background(const Vector2DInt & size, ResourceArchive * archive);
	static void generate_resources(ResourceArchive * archive);
	static bool m_initialized;
	static GameObject * m_background;
	static std::map<Vector2DInt, std::vector<GameObject*>*> m_objects;
};