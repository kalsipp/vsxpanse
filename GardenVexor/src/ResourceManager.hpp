#pragma once
#include <vector>
#include <map>
#include <algorithm> 
class ResourceCmp;
enum RESOURCE_TYPE
{
	GENERIC
};
class ResourceManager
{
public:
	static void initialize();
	static void teardown();
	static void register_resource(ResourceCmp* rescmp);
	static void unregister_resource(ResourceCmp * rescmp);
	static ResourceCmp * get_resource_closest_to_center(RESOURCE_TYPE resource);
private:
	ResourceManager() {}
	static bool m_initialized;
	static std::map<RESOURCE_TYPE, std::vector<ResourceCmp*>> m_resource_heap;
};