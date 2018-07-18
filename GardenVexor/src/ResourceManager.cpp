#include "resourcemanager.hpp"
#include "components/resource_cmp.hpp"
std::map<RESOURCE_TYPE, std::vector<ResourceCmp*>> ResourceManager::m_resource_heap;
bool ResourceManager::m_initialized;


void ResourceManager::initialize()
{

}

void ResourceManager::teardown()
{
	m_resource_heap.clear();
}

void ResourceManager::register_resource(ResourceCmp * rescmp)
{
	struct heap_comparer
	{
		bool operator()(const ResourceCmp* a, const ResourceCmp* b) const
		{
			return a->get_distance_to_center() > b->get_distance_to_center();
		}
	};
	ASSERT(rescmp != nullptr, "ResourceCmp is null");
	const RESOURCE_TYPE type = rescmp->get_resource_type();
	if (m_resource_heap.count(type) == 0)
	{
		m_resource_heap[type] = std::vector<ResourceCmp*>();
	}
	m_resource_heap[type].push_back(rescmp);
	std::make_heap(m_resource_heap[type].begin(), m_resource_heap[type].end(), heap_comparer());
	
}

void ResourceManager::unregister_resource(ResourceCmp * rescmp)
{
	ASSERT(rescmp != nullptr, "ResourceCmp is null");
	const RESOURCE_TYPE type = rescmp->get_resource_type();
	ASSERT(m_resource_heap.count(type), "This kind of resource has not been registered yet");
	for (auto it = m_resource_heap[type].begin(); it != m_resource_heap[type].end(); ++it)
	{
		if (*it == rescmp)
		{
			m_resource_heap[type].erase(it);
			return;
		}
	}
	ASSERT(false, "That resource was never registered");
}

ResourceCmp * ResourceManager::get_resource_closest_to_center(RESOURCE_TYPE resource)
{
	if (m_resource_heap.count(resource) == 0) return nullptr;
	return m_resource_heap[resource][0];
}