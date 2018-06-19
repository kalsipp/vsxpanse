#pragma once
typedef unsigned long GAMEOBJECT_ID;

#include <vector>
#include <string>
#include <map>
#include "component.hpp"
#include "components/transform.hpp"
#include "basics/vector3d.hpp"
#include "basics/logging.hpp"

class Component;
struct ComponentSettings;
class GameObject {
public:
	GameObject(GAMEOBJECT_ID id);
	virtual ~GameObject();
	bool & enabled();

	template <typename component_type>
	component_type * add_component();

	template <class component_type>
	component_type * get_component();

	std::vector<Component*> & get_all_components();

	virtual void update() {}
	void update_components();
	void update_colliders();
	void render();
	void destroy();
	Transform & transform();
	const Transform & transform() const;
	GAMEOBJECT_ID id()const;
	std::string & name();
protected:
	bool m_enabled = true;
	std::string m_name = "NoName";
	const GAMEOBJECT_ID m_id;
	std::vector<Component*> m_components;
	std::multimap<size_t, Component*> m_component_types;
	Transform m_transform;
};


template <typename component_type>
component_type * GameObject::add_component() {
	component_type * new_comp_type = new component_type();
	m_components.push_back(new_comp_type);
	m_component_types.insert(std::make_pair(typeid(component_type).hash_code(), new_comp_type));
	Logging::log(std::stringstream() << "Adding component " << typeid(component_type).name(), Logging::TRACE);
	return new_comp_type;
}

template <class component_type>
component_type * GameObject::get_component() {
	auto iter = m_component_types.find(typeid(component_type).hash_code());
	if (iter != m_component_types.end()) {
		return (component_type*)(iter->second);
	} else {
		return nullptr;
	}
}
