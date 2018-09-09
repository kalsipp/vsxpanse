#include "gameobject.hpp"
#include "engine.hpp"
GameObject::GameObject(GAMEOBJECT_ID id): m_id(id) {
}

GameObject::~GameObject() {
	m_components.clear();
}

bool & GameObject::enabled() {
	return m_enabled;
}

void GameObject::setup()
{
	for (auto i = m_components.begin(); i != m_components.end(); ++i)
	{
		(*i)->setup();
	}
}


void GameObject::teardown()
{
	for (auto i = m_components.begin(); i != m_components.end(); ++i)
	{
		(*i)->teardown();
	}
}



void GameObject::update_collision()
{
	if (!m_enabled) return;
	for (auto i = m_components.begin(); i != m_components.end(); ++i)
	{
		(*i)->collision_step();
	}
}

void GameObject::update_components() {
	if (!m_enabled) return;
	for (auto i = m_components.begin(); i != m_components.end(); ++i) {
		(*i)->update();
	}
}

void GameObject::render() {
	if (!m_enabled) return;
	for (auto i = m_components.begin(); i != m_components.end(); ++i) {
		(*i)->render();
	}

}

void GameObject::destroy() {
	Engine::remove_gameobject(this);
}

Transform & GameObject::transform() {
	return m_transform;
}
const Transform & GameObject::transform() const {
	return m_transform;
}

GAMEOBJECT_ID GameObject::id()const {
	return m_id;
}
std::string & GameObject::name() {
	return m_name;
}
