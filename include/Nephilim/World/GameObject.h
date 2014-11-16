#ifndef NephilimGameObject_h__
#define NephilimGameObject_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/EntityManager.h>
#include <Nephilim/World/CHandle.h>
#include <Nephilim/World/CTransform.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API GameObject
{
public:
	TEntity rootEntity;

	component_ptr<CTransform> transform;

public:
	
};

NEPHILIM_NS_END
#endif // NephilimGameObject_h__
