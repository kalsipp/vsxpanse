#include <algorithm>

#include "engine.hpp"
#include "inputmanager.hpp"
#include "graphicsmanager.hpp"
#include "basics/timer.hpp"
#include "components/debug_closegamecomponent.hpp"
#include "components/textcomponent.hpp"
#include "physxengine.hpp"

std::map<std::string, void(*)()> Engine::m_scenes;
std::string Engine::m_scene_to_load = "";
bool Engine::m_about_to_load_scene = false;
bool Engine::m_running = false;
bool Engine::m_initialized = false;
GAMEOBJECT_ID Engine::m_latest_gameobject_id = 0;
std::vector<GameObject *> Engine::m_gameobjects;
std::queue<GameObject*> Engine::m_gameobjects_to_add;
std::vector<GameObject*> Engine::m_gameobjects_to_remove;
ResourceArchive Engine::m_engine_resources("EngineResources");
GameObject * g_debug_texttime;


void set_up_logging() {
	Logging::add_file("info.log", Logging::INFO);
	Logging::add_file("warnings.log", Logging::WARNING);
	Logging::add_file("errors.log", Logging::ERROR);
	Logging::log("NICE LOGGING", Logging::INFO);
}

void set_up_stacktrace() {
	//Debug from helpers.hpp
#ifdef __GNUC__
	signal(SIGSEGV, sig_error_handler);
	signal(SIGABRT, sig_error_handler);
	signal(SIGINT, sig_error_handler);
#endif
}

void Engine::load_default_resources()
{

}

/* Public routines */
void Engine::initialize() {
	ASSERT(!Engine::m_initialized, "You can't initialize engine twice!");
	set_up_stacktrace();
	set_up_logging();
	load_default_resources();
	GraphicsManager::initialize();
	InputManager::initialize();
	PhysxEngine::initialize();
	Engine::m_initialized = true;
	Logging::log("Finished initialize Engine", Logging::INFO);
}

void Engine::teardown() {

	clear_all_gameobjects();
	PhysxEngine::teardown();
	GraphicsManager::teardown();
	Logging::log("Finished teardown Engine", Logging::INFO);
	Logging::teardown();
	Engine::m_initialized = false;
}

void Engine::start() {
	ASSERT(Engine::m_initialized, "You need to initialize engine first!");
	Engine::m_running = true;
	Logging::log("Starting Engine", Logging::INFO);
	Engine::main_loop();
}

void Engine::stop() {
	Engine::m_running = false;
}

//GameObject * Engine::get_gameobject(const GAMEOBJECT_ID id) {
//	if (!Engine::m_gameobjects.count(id)) return nullptr;
//	return Engine::m_gameobjects[id];
//}

void Engine::remove_gameobject(GameObject * gObj) {

	Engine::m_gameobjects_to_remove.push_back(gObj);
}

size_t Engine::get_gameobject_count() {
	return Engine::m_gameobjects.size();
}

void Engine::register_scene(const std::string & name, void (*scenecreator)()) {
	Engine::m_scenes[name] = scenecreator;
}

void Engine::load_scene(const std::string & name) {
	ASSERT(m_scenes.count(name), "No scene named " + name);
	m_scene_to_load = name;
	m_about_to_load_scene = true;
}
/* Private routines*/

void Engine::main_loop() {
	double ms_p_frame = 0.016666667 * 1000;
	(void)ms_p_frame;
	while (Engine::m_running) {
		if (m_about_to_load_scene) {
			m_about_to_load_scene = false;
			replace_scene();
		}
		Timer tim;
		tim.start();
		Engine::put_gameobjects_into_world();
		Engine::remove_gameobject_from_world();
		InputManager::read_inputs();
		PhysxEngine::update();
		Engine::update_gameobjects();
		int64_t time = tim.get_elapsed_milliseconds();
		g_debug_texttime->get_component<TextComponent>()->set_text(std::to_string(time) + "ms");
		Engine::render_gameobjects();
	}
}

void Engine::replace_scene() {
	/*
		Removes all gameobjects
		calls the sceneloader function
		this function will add the
		intial gameobjects to the engine.
	*/
	clear_all_gameobjects();
	m_scenes[m_scene_to_load]();
}


void Engine::update_gameobjects() {
	for (auto go = Engine::m_gameobjects.begin();
	        go != Engine::m_gameobjects.end(); ++go) {
		(*go)->update_components();
	}
}

bool debug_render_colliders = true;

void Engine::render_gameobjects() {

	GraphicsManager::prepare_rendering();
	/* Temp for collider debugging */
	if (InputManager::get_key(SDL_SCANCODE_LCTRL) && InputManager::get_key_down(SDL_SCANCODE_K))
	{
		debug_render_colliders = !debug_render_colliders;
	}
	if (debug_render_colliders)
	{
		GraphicsManager::set_render_draw_color(0xff, 0xff, 0xff, 0xff);
		PhysxEngine::render();
	}
	else
	{
		for (auto go = m_gameobjects.begin();
			go != m_gameobjects.end(); ++go)
		{
			(*go)->render();
		}
	}
	//GraphicsManager::set_render_draw_color(0xff, 0xff, 0xff, 0xff);
	//GraphicsManager::draw_line(Vector2D(0, 0), Vector2D(10, 10));
	//GraphicsManager::draw_line(Vector2D(10, 10), Vector2D(20, 0));
	//GraphicsManager::draw_line(Vector2D(20, 0), Vector2D(0, 0));
	GraphicsManager::execute_rendering();
}

//bool compare_gameobjects_zpos(const GameObject* a, const GameObject* b) {
//	return (a->transform().get_position().z < b->transform().get_position().z);
//}

void Engine::clear_all_gameobjects() {
	m_gameobjects.clear();
	std::queue<GameObject*>().swap(m_gameobjects_to_add);
	std::vector<GameObject*>().swap(m_gameobjects_to_remove);
	
	auto g = Engine::add_gameobject<GameObject>();
	g->add_component<Debug_CloseGameComponent>();
	g->name() = "Debug_CloseGameComponent";
	ResourceFile * font = m_engine_resources.get_item("Fonts\\calibri.ttf");
	g_debug_texttime = Engine::add_gameobject<GameObject>();
	g_debug_texttime->transform().move(Vector2D(20, 0));
	g_debug_texttime->add_component<TextComponent>()->initialize(font, 64);
}

void Engine::put_gameobjects_into_world() {
	std::vector<GameObject*> added_items(Engine::m_gameobjects_to_add.size());
	size_t added_objects = 0;
	while (!Engine::m_gameobjects_to_add.empty()) {
		GameObject* new_item = Engine::m_gameobjects_to_add.front();
		Engine::m_gameobjects_to_add.pop();
		

		/* Does insert sort based on z - position 
		   to decide render order.
		   large z = rendered later = "on top" / "closer to camera"
		*/
		int indx = 0;
		for (; indx != m_gameobjects.size(); ++indx)
		{
			if (new_item->transform().get_position().z <= m_gameobjects[indx]->transform().get_position().z)
			{
				m_gameobjects.insert(m_gameobjects.begin()+indx, new_item);
				break;
			}
		}
		if (indx == m_gameobjects.size())
		{
			m_gameobjects.push_back(new_item);
		}
		added_items[added_objects] = new_item;
		added_objects++;
	}

	Engine::run_setups(added_items);
}
void Engine::remove_gameobject_from_world() {

	for (auto gObj_to_remove = m_gameobjects_to_remove.begin();
		gObj_to_remove != m_gameobjects_to_remove.end();
		++gObj_to_remove
		)
	{
		for (auto gObj_in_world = m_gameobjects.begin();
			gObj_in_world != m_gameobjects.end();
			++gObj_in_world
			)
		{
			if ((*gObj_in_world) == (*gObj_to_remove))
			{
				(*gObj_to_remove)->teardown();
				m_gameobjects.erase(gObj_in_world);
				delete *gObj_in_world;
				break;
			}
		}
	}

	//while (!Engine::m_gameobjects_to_remove.empty()) {
	//	GameObject * gObj = Engine::m_gameobjects_to_remove.front();
	//	ASSERT(gObj != nullptr, "Trying to remove null gObject");
	//	gObj->teardown();
	//	Engine::m_gameobjects_to_remove.pop();
	//	for (auto go = Engine::m_gameobjects.begin();
	//		go != Engine::m_gameobjects.end(); ++go)
	//	{
	//		if ((*go) == gObj)
	//		{
	//			Engine::m_gameobjects.erase
	//		}
	//	}
	//		Engine::m_gameobjects.
	//}
}


void Engine::run_setups(std::vector<GameObject*> & gameobjects) {

	for (auto go = gameobjects.begin(); go != gameobjects.end(); ++go) {
		(*go)->setup();
	}
}

