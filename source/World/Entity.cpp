#include <Nephilim/World/Entity.h>

NEPHILIM_NS_BEGIN

bool operator==(Entity& e1, Entity& e2)
{
	return e1.id == e2.id;
}

bool operator<(const Entity e1, const Entity e2)
{
	return e1.id < e2.id;
}

NEPHILIM_NS_END