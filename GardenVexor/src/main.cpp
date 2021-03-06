#include "engine.hpp"
#include "components/transform.hpp"
#include "components/spritecomponent.hpp"
#include "components/playercontroller_cmp.hpp"
#include "components/harvestercontroller_cmp.hpp"
#include "components/guicontrol_cmp.hpp"
#include "components/resource_cmp.hpp"
#include "components/debugcomponent.hpp"
#include "map/gridmap.hpp"
#include "map/astar.hpp"
#include "basics/timer.hpp"
#include "map/gridbackground.hpp"
#include "map/gridmap.hpp"
#undef main


ResourceArchive * g_archive;

void setup_generic_resource(Vector2DInt pos)
{
	GameObject * resource = Engine::add_gameobject<GameObject>();
	resource->transform().set_position(pos);
	ResourceFile * file = g_archive->get_item("Images\\resource.png");
	resource->add_component<SpriteComponent>()->load_sprite_from_image(file);
	ResourceCmp * rcmp = resource->add_component<ResourceCmp>();
	rcmp->initialize(Vector2DInt(0,0), GENERIC);
}

void generate_resources()
{
	setup_generic_resource(Vector2DInt(200, 200));
	setup_generic_resource(Vector2DInt(300, 300));
	setup_generic_resource(Vector2DInt(450, 600));
	
}

void set_up_a_harvester()
{
	GameObject * harv = Engine::add_gameobject<GameObject>();
	harv->name() = "Harvester";
	SpriteComponent * sc = harv->add_component<SpriteComponent>();
	ResourceFile * file = g_archive->get_item("Images\\harvester.png");
	sc->load_sprite_from_image(file);
	Harvester * hrv = harv->add_component<Harvester>();
	GridMapUser * gridcmp = harv->add_component<GridMapUser> ();
	gridcmp->solid() = true;
}

void set_up_player()
{
	GameObject * player = Engine::add_gameobject<GameObject>();
	player->name() = "Player";
	SpriteComponent * sc = player->add_component<SpriteComponent>();
	ResourceFile * file = g_archive->get_item("Images\\player.png");
	player->add_component<PlayerControllerCmp>();
	player->transform().set_position(Vector2D(10, 10));
	sc->load_sprite_from_image(file);
	player->add_component<DebugComponent>();
}

void set_up_gui_controls()
{
	GameObject * gui = Engine::add_gameobject<GameObject>();
	gui->add_component<GuiControlCmp>();
}

void make_red_square(Vector2DInt pos)
{
	GameObject * sqr = Engine::add_gameobject<GameObject>();
	sqr->name() = "benis";
	sqr->transform().set_position(pos*32);
	SpriteComponent * sc = sqr->add_component<SpriteComponent>();
	ResourceFile * file = g_archive->get_item("Images\\player.png");
	sc->load_sprite_from_image(file);
}

void set_up_blockade()
{
	for (int i = 0; i < 10; ++i)
	{
		Vector2DInt pos(400, 20 * i);
		
		GameObject * obj = Engine::add_gameobject<GameObject>();
		obj->name() = "blokr";
		obj->transform().set_position(pos);

		ResourceFile * file = g_archive->get_item("Images\\resource.png");
		GridMapUser * grcmp =  obj->add_component<GridMapUser>();
		grcmp->solid() = true;
		Agent * uni = obj->add_component<Agent>();
		SpriteComponent * comp = obj->add_component<SpriteComponent>();
		comp->load_sprite_from_image(file);

	}
}
void set_up_gameobjects()
{
	set_up_player();
	set_up_a_harvester();
	set_up_blockade();
	generate_resources();
	set_up_gui_controls();
}




int main()
{
	Engine::initialize();
	g_archive = new ResourceArchive("Resources");
	GridMap::initialize(g_archive);
	Engine::register_scene("tmp", set_up_gameobjects);
	Engine::load_scene("tmp");
	Engine::start();
	Engine::teardown();
	GridMap::teardown();
    return 0;
}

	