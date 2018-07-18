#include <math.h> 
#include "gridmap.hpp"
#include "engine.hpp"
#include "components/spritecomponent.hpp"


/* TILEINFO */
bool TileInfo::is_free()const { return m_solidness == FREE_POSITION; }
void TileInfo::register_solid_object() { ++m_solidness; }
void TileInfo::deregister_solid_object() { 
	--m_solidness; 
	ASSERT(m_solidness >= 0, "Solidness reached bad value");
}
void TileInfo::register_agent(GameObject * obj, bool solid) 
{ 
	m_gameobjects.push_back(obj); 
	if (solid) register_solid_object();
}
void TileInfo::deregister_agent(GameObject * obj, bool solid)
{
	ASSERT(m_gameobjects.size() != 0, "Can't deregister unit when there's nothing around");
	for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it)
	{
		if (*it == obj)
		{
			m_gameobjects.erase(it);
			break;
		}
	}
	if (solid) deregister_solid_object();
}


/* GRIDMAP */
TileInfo *** GridMap::m_objects;
bool GridMap::m_initialized = false;
Vector2DInt GridMap::m_size;

void GridMap::initialize(ResourceArchive * archive)
{
	ASSERT(!m_initialized, "You can not initialize GridMap twice");
	m_size = Vector2DInt(GRIDMAPSIZE, GRIDMAPSIZE);
	m_objects = new TileInfo**[m_size.y];
	for (int y = 0; y < m_size.y; ++y)
	{
		m_objects[y] = new TileInfo*[m_size.x];
		for (int x = 0; x < m_size.x; ++x)
		{
			m_objects[y][x] = new TileInfo();
		}
	}
	generate_resources(archive);
	m_initialized = true;
}

void GridMap::teardown()
{
	for (int y = 0; y < m_size.y; ++y)
	{
		for (int x = 0; x < m_size.x; ++x)
		{
			delete m_objects[y][x];
		}
		delete m_objects[y];
	}
	delete m_objects;

	m_initialized = false;
}

bool GridMap::move_unit(GameObject * unit, const Vector2DInt & pixelpos_to, bool solid)
{

	Vector2DInt src(unit->transform().get_position());
	src = pixelspace_to_gridspace(src);
	Vector2DInt dst(pixelspace_to_gridspace(pixelpos_to));
	TileInfo * const src_tile = get_tileinfo(src);
	TileInfo * const dst_tile = get_tileinfo(dst);
	if (dst_tile->is_free())
	{
		src_tile->deregister_agent(unit, solid);
		dst_tile->register_agent(unit, solid);
		Vector2DInt pixelpos_gridcapped = gridspace_to_pixelspace(dst);
		unit->transform().set_position(pixelpos_gridcapped);
		return true;
	}
	else
	{
		return false;
	}
}

void GridMap::register_unit(GameObject * const unit, bool solid)
{

	Vector2DInt gridpos(unit->transform().get_position());
	gridpos = pixelspace_to_gridspace(gridpos);
	TileInfo * const tile = get_tileinfo(gridpos);
	tile->register_agent(unit, solid);
	Vector2DInt pixelpos_gridcapped = gridspace_to_pixelspace(gridpos);
	unit->transform().set_position(pixelpos_gridcapped);
}

void GridMap::register_unit(GameObject * const unit, const Vector2DInt & pixelpos, bool solid)
{
	Vector2DInt gridpos = pixelspace_to_gridspace(pixelpos);
	TileInfo * const tile = get_tileinfo(gridpos);
	tile->register_agent(unit, solid);
	Vector2DInt pixelpos_gridcapped = gridspace_to_pixelspace(gridpos);
	unit->transform().set_position(pixelpos_gridcapped);
}


void add_resource(ResourceArchive * archive)
{
	GameObject * obj = Engine::add_gameobject<GameObject>();
	ResourceFile * file = archive->get_item("Images\\resource.png");
	obj->add_component<SpriteComponent>()->load_sprite_from_image(file);
	obj->transform().set_position(Vector2D(300, 300));
}

void GridMap::generate_resources(ResourceArchive * archive)
{
	add_resource(archive);
}

TileInfo * const GridMap::get_tileinfo(const Vector2DInt & gridpos)
{
	ASSERT(get_if_position_in_gridmap(gridpos), "Out of GridMap bounds");
	return m_objects[gridpos.y][gridpos.x];
}

int GridMap::get_min_x() { return 0; }
int GridMap::get_min_y() { return 0; }
int GridMap::get_max_x() { return m_size.x; }
int GridMap::get_max_y() { return m_size.y; }

bool GridMap::get_if_tile_is_free(const Vector2DInt & gridpos)
{
	ASSERT(get_if_position_in_gridmap(gridpos), "Out of GridMap bounds");
	return get_tileinfo(gridpos)->is_free();
}
const Vector2DInt & GridMap::get_size() { return m_size; }

bool GridMap::get_if_position_in_gridmap(const Vector2DInt & pos)
{
	return pos.x >= get_min_x() &&
		pos.x < get_max_x() &&
		pos.y >= get_min_y() &&
		pos.y < get_max_y();
}



Vector2DInt GridMap::pixelspace_to_gridspace(const Vector2DInt & pixelpos)
{
	return Vector2DInt(pixelspace_to_gridspace(pixelpos.x), pixelspace_to_gridspace(pixelpos.y));
}

int GridMap::pixelspace_to_gridspace(int value)
{
	if (value >= 0)
	{
		return value / GRIDTILESIZE;
	}
	else
	{
		/* Negative integer division is odd, it floors to 0 instead of negative.
		This ensures that is falls into the right tile.
		*/
		return (value - GRIDTILESIZE + 1) / GRIDTILESIZE;
	}
}

Vector2DInt GridMap::gridspace_to_pixelspace(const Vector2DInt & gridpos)
{
	return Vector2DInt(gridspace_to_pixelspace(gridpos.x), gridspace_to_pixelspace(gridpos.y));
}

int GridMap::gridspace_to_pixelspace(int value)
{
	return value * GRIDTILESIZE;
}