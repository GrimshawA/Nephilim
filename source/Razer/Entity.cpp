#include <Nephilim/Razer/Scene.h>

NEPHILIM_NS_BEGIN
namespace rzr{

EntityInternal::EntityInternal()
: mId(0)
{

}

EntityInternal::EntityInternal(entity_id_type id)
: mId(id)
{

}

};
NEPHILIM_NS_END