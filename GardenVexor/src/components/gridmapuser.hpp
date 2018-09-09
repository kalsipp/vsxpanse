#pragma once
#include <stack>
#include "component.hpp"

enum MOVEMENT_STATUS
{
	SUCCESSFUL_MOVE, 
	NO_MOVE_PATH_DONE,
	COULD_NOT_MOVE
};

class Agent;
class GridMapUser:public Component
{
public:
	GridMapUser(GameObject * owner):Component(owner) {}
	void setup()override;
	
	/*------------------------------------
	Move to the designated tile.
	--------------------------------------
	Returns:   bool, if it was possible to move.
	Parameter: const Vector2DInt & dst
	------------------------------------*/
	bool move_in_grid(const Vector2DInt & dst);
	
	/*------------------------------------
	Calculates the quickest path to the destination
	--------------------------------------
	Returns:   bool, true if it was possible to find a path.
	Parameter: const Vector2DInt & dst
	------------------------------------*/
	bool calculate_path(const Vector2DInt & dst);
	
	/*------------------------------------
	Gets the next step in the pre-calculated pathfinder path. 
	--------------------------------------
	Returns:   bool, returns true if next position was properly populated. False if there are no more steps.
	Parameter(out): Vector2DInt & outp, The position to populate.
	------------------------------------*/
	bool get_next_pathfinder_step(Vector2DInt & outp);

	MOVEMENT_STATUS move_to_next_pathfinder_step();

	/*------------------------------------
	Get number of pathfinder steps left.
	--------------------------------------
	Returns:   size_t
	------------------------------------*/
	size_t get_num_pathfinder_steps_left();

	/*------------------------------------
	If this unit is determined to be solid/collidable or not.
	--------------------------------------
	Returns:   bool &
	------------------------------------*/
	bool & solid() { return m_solid; }

	void clear_pathfinder_path();

private:
	bool m_solid;
	Agent * m_agent;
	std::stack<Vector2DInt> m_pathfind_path;
};