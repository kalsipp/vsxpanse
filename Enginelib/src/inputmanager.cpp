#include "inputmanager.hpp"

/*-------------------------------------------------------
	Parameters.
---------------------------------------------------------*/

bool InputManager::m_initialized = false;
std::string InputManager::m_text_input = "";
std::map<int, bool> InputManager::m_key_states_current;
std::map<int, bool> InputManager::m_mouse_states;
std::map<int, bool> InputManager::m_mouse_states_current;
std::map<int, SDL_MouseButtonEvent> InputManager::m_mouse_latest_event;
SDL_Event InputManager::m_sdl_event;
std::map<int, bool> InputManager::m_key_states;

/*Publics*/
void InputManager::initialize() {
	if (!InputManager::m_initialized) {
		InputManager::m_initialized = true;
	}
}

void InputManager::read_inputs() {
	InputManager::reset_keys();
	InputManager::reset_text_input();
	
	while (SDL_PollEvent(&InputManager::m_sdl_event) != 0) {
		switch (InputManager::m_sdl_event.type) {

		//If the window cross is pressed.
		case SDL_QUIT:
			InputManager::set_key(INPUT_KEY_QUIT, true);
			break;
		//If continuous text if being added
		case SDL_TEXTINPUT:
			InputManager::add_text_input(InputManager::m_sdl_event.text.text);
			break;
		//On key up
		case SDL_KEYUP:
			InputManager::set_key(InputManager::m_sdl_event.key.keysym.scancode, false);
			break;
		//On key down
		case SDL_KEYDOWN:
			if (!InputManager::m_sdl_event.key.repeat) {
				InputManager::set_key(InputManager::m_sdl_event.key.keysym.scancode, true);
			}
			break;
		//On mouse up
		case SDL_MOUSEBUTTONDOWN:
			InputManager::set_mouse(m_sdl_event.button.button, true, m_sdl_event.button);
			break;
		//On mouse down
		case SDL_MOUSEBUTTONUP:
			InputManager::set_mouse(m_sdl_event.button.button, false, m_sdl_event.button);
			break;
		}
	}

}

bool InputManager::get_key(int key) {
	if(!m_key_states.count(key)) return false;
	return m_key_states[key];
}
bool InputManager::get_key_down(int key) {
	if (InputManager::m_key_states_current.count(key) == 0) return false;
	return InputManager::m_key_states_current[key];
}

bool InputManager::get_mouse(int mousebtn)
{
	if (InputManager::m_mouse_states.count(mousebtn) == 0) return false;
	return InputManager::m_mouse_states[mousebtn];
}

bool InputManager::get_mouse_down(int mousebtn)
{
	if (InputManager::m_mouse_states_current.count(mousebtn) == 0) return false;
	return InputManager::m_mouse_states_current[mousebtn];
}
bool InputManager::get_latest_mouse_event(int mousebtn, SDL_MouseButtonEvent * evnt)
{
	if (m_mouse_latest_event.count(mousebtn))
	{
		*evnt = m_mouse_latest_event[mousebtn];
		return true;
	}else
	{
		return false;
	}
}

Vector2DInt InputManager::get_mouse_position()
{
	Vector2DInt container;
	SDL_GetMouseState(&container.x, &container.y);
	return container;
}

/*Privates*/

void InputManager::set_key(int key, bool val) {
	InputManager::m_key_states[key] = val;
	if(val)	InputManager::m_key_states_current[key] = val;
}

void InputManager::reset_keys() {
	InputManager::m_key_states_current.clear();
	InputManager::m_mouse_states_current.clear();
}

void InputManager::add_text_input(const std::string & text) {
	InputManager::m_text_input += text;
}

void InputManager::reset_text_input() {
	InputManager::m_text_input = "";
}

void InputManager::set_mouse(int key, bool val, const SDL_MouseButtonEvent & evnt) {
	InputManager::m_mouse_states[key] = val;
	if (val) InputManager::m_mouse_states_current[key] = val;
	InputManager::m_mouse_latest_event[key] = evnt;
}