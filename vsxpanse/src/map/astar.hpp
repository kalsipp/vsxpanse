#pragma once
#include "basics/vector2dint.hpp"
#include <stack>
class TileInfo;
class Astar
{
public:
	/*------------------------------------
	Get path in the grid from a position, to a position.
	--------------------------------------
	Returns:   bool, if it was possible to find a path
	Parameter: Vector2DInt from, pixelspace position
	Parameter: Vector2DInt to, pixelspace position
	Parameter(out): std::stack<Vector2DInt> & path, will be populated with the path
		Not changed if no good path is found.
	------------------------------------*/
	static bool get_path(Vector2DInt from, Vector2DInt to, std::stack<Vector2DInt> & path);
	
	/*------------------------------------
	Gets the closest position next to the designated position.
	Used when your target position is blocked, but you want to find a nearby position.
	--------------------------------------
	Returns:   bool if it was possible to find a position
	Parameter: Vector2DInt target, around which position we should check
	Parameter(out): Vector2DInt * out_position, becomes populated with a nearby position. 
		Not changed if no good position is found.
	------------------------------------*/
	static bool find_position_near_position(Vector2DInt target, Vector2DInt * out_position);
private:
	Astar() {}
};