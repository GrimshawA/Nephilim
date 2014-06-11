#ifndef NephilimRazerSystemBulletPhysics_h__
#define NephilimRazerSystemBulletPhysics_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/System.h>

#include <Nephilim/BxScene.h>
#include <Nephilim/BxBody.h>

NEPHILIM_NS_BEGIN
namespace rzr 
{

/**
	\class SystemBullet
	\brief 
*/
class NEPHILIM_API SystemBullet : public System
{
public:
	SystemBullet();

	virtual void update(const Time& deltaTime);

	BxScene bulletWorld;

};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystemBulletPhysics_h__
