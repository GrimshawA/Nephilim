#ifndef NephilimComponentWater2_h__
#define NephilimComponentWater2_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN

namespace rzr {

/**
	\class ComponentWater2
	\brief 
*/
class NEPHILIM_API ComponentWater2 : public Component
{
public:
	ComponentWater2();

	void init();

	void render(Renderer* mRenderer);

	bool ready;
};

};
NEPHILIM_NS_END
#endif // NephilimComponentWater2_h__
