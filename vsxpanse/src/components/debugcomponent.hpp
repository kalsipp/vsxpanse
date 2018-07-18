#include "component.hpp"

class ResourceArchive;
class DebugComponent : public Component
{
public:
	DebugComponent(GameObject * owner):Component(owner){}
	void setup()override;
	void update()override;
	std::vector<GameObject*> markers;
	ResourceArchive * arch;
};