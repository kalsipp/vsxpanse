#include "gridmap.hpp"
#include "engine.hpp"
#include "gridbackground.hpp"
#include "components/spritecomponent.hpp"
GameObject * GridMap::m_background;
std::map<Vector2DInt, std::vector<GameObject*> *> GridMap::m_objects;
bool GridMap::m_initialized = false;
Vector2DInt GridMap::m_size;

void GridMap::initialize(const Vector2DInt & size, ResourceArchive * archive)
{
	ASSERT(!m_initialized, "You can not initialize GridMap twice");
	add_background(size, archive);
	m_size = size;
	for (int x = 0; x < m_size.x; ++x)
	{
		for (int y = 0; y < m_size.y; ++y)
		{
			m_objects[Vector2DInt(x, y)] = new std::vector<GameObject*>();
		}
	}
	generate_resources(archive);
	m_initialized = true;
}

void GridMap::teardown()
{
	for (int x = 0; x < m_size.x; ++x)
	{
		for (int y = 0; y < m_size.y; ++y)
		{
			/* GameObjects will be removed by Engine */
			delete m_objects[Vector2DInt(x, y)];
		}
	}
	m_initialized = false;
}

bool GridMap::move_unit(GameObject * unit, const Vector2DInt & from, const Vector2DInt & to)
{
	
	return true;
}

void GridMap::add_background(const Vector2DInt & size, ResourceArchive * archive)
{
	m_background = Engine::add_gameobject<GameObject>();
	m_background->add_component<GridBackground>()->initialize(size, archive);
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

std::vector<GameObject*>* GridMap::get_objects_at_position(const Vector2DInt & pos)
{
	ASSERT(m_objects.count(pos), "Out of GridMap bounds");
	return m_objects[pos];
}