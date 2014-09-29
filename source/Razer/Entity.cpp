#include <Nephilim/Razer/Entity.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

Entity::Entity()
: mScene(nullptr)
{

}

Entity::Entity(TEntity e, Scene& s)
: mScene(&s)
, id(e)
{

}

};
NEPHILIM_NS_END