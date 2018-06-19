#include <algorithm>

#include "engine.hpp"
#include "graphicsmanager.hpp"
#include "basics/timer.hpp"
#include "components/debug_closegamecomponent.hpp"
#include "components/textcomponent.hpp"

std::map<std::string, void(*)()> Engine::m_scenes;
std::string Engine::m_scene_to_load = "";
bool Engine::m_about_to_load_scene = false;
bool Engine::m_running = false;
bool Engine::m_initialized = false;
std::map<GAMEOBJECT_ID, GameObject*> Engine::m_gameobjects;
GAMEOBJECT_ID Engine::m_latest_gameobject_id = 0;
std::queue<std::pair<GAMEOBJECT_ID, GameObject*>> Engine::m_gameobjects_to_add;
std::queue<GAMEOBJECT_ID> Engine::m_gameobjects_to_remove;
ResourceArchive Engine::m_engine_resources("EngineResources");
GameObject * g_debug_texttime;


void set_up_logging() {
	Logging::add_file("everything.log", Logging::TRACE);
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
	Engine::m_initialized = true;
	Logging::log("Finished initialize Engine", Logging::INFO);
}

void Engine::teardown() {

	clear_all_gameobjects();
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

GameObject * Engine::get_gameobject(const GAMEOBJECT_ID id) {
	if (!Engine::m_gameobjects.count(id)) return nullptr;
	return Engine::m_gameobjects[id];
}

void Engine::remove_gameobject(const GAMEOBJECT_ID id) {

	Engine::m_gameobjects_to_remove.push(id);
	Logging::log("Removing gameobject id " + std::to_string(id), Logging::TRACE);
}

unsigned long Engine::get_gameobject_count() {
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
		(*go).second->update_components();
	}
	for (auto go = Engine::m_gameobjects.begin();
	        go != Engine::m_gameobjects.end(); ++go) {
		(*go).second->update();
	}
}

void Engine::render_gameobjects() {
	std::vector<GameObject *> items_to_render;

	Engine::sort_gameobjects(items_to_render);
	GraphicsManager::prepare_rendering();
	for (auto go = items_to_render.begin();
	        go != items_to_render.end(); ++go) {
		(*go)->render();
	}
	GraphicsManager::execute_rendering();
}

bool compare_gameobjects(const GameObject* a, const GameObject* b) {
	return (a->transform().get_position().z < b->transform().get_position().z);
}

void Engine::sort_gameobjects(std::vector<GameObject*>& objs) {

	//fill items
	for (auto i = m_gameobjects.begin(); i != m_gameobjects.end(); ++i) {
		objs.push_back(i->second);
	}
	//sort by value using std::sort
	std::sort(objs.begin(), objs.end(), compare_gameobjects);
}


void Engine::clear_all_gameobjects() {
	m_gameobjects.clear();
	std::queue<std::pair<GAMEOBJECT_ID, GameObject*>>().swap(m_gameobjects_to_add);
	std::queue<GAMEOBJECT_ID>().swap(m_gameobjects_to_remove);
	
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
	GAMEOBJECT_ID added_items_counter = 0;
	while (!Engine::m_gameobjects_to_add.empty()) {
		std::pair<GAMEOBJECT_ID, GameObject*> new_item = Engine::m_gameobjects_to_add.front();
		Engine::m_gameobjects_to_add.pop();
		Engine::m_gameobjects[new_item.first] = new_item.second;
		added_items[added_items_counter] = new_item.second;
		++added_items_counter;
	}

	Engine::run_setups(added_items);
}
void Engine::remove_gameobject_from_world() {
	while (!Engine::m_gameobjects_to_remove.empty()) {
		GAMEOBJECT_ID id = Engine::m_gameobjects_to_remove.front();
		if (Engine::m_gameobjects.count(id)) {
			for (auto comp = Engine::m_gameobjects[id]->get_all_components().begin();
			        comp != Engine::m_gameobjects[id]->get_all_components().end();
			        ++comp) {
				(*comp)->teardown();
			}
			Engine::m_gameobjects_to_remove.pop();
			Engine::m_gameobjects.erase(id);
		}
	}
}


void Engine::run_setups(std::vector<GameObject*> & gameobjects) {

	for (auto go = gameobjects.begin(); go != gameobjects.end(); ++go) {
		for (auto comp = (*go)->get_all_components().begin();
		        comp != (*go)->get_all_components().end();
		        ++comp) {
			(*comp)->setup(*go);
		}
	}
}

