#ifndef NephilimRazerComponentGizmo_h__
#define NephilimRazerComponentGizmo_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN

namespace rzr {

/**
	\class CGizmo
	\brief Entities with this component will have a transform gizmo rendered in them

	Transform gizmos are displayed using a gizmo component.
	This allows for custom renderers to easily change the aspect of the gizmos.
*/
class NEPHILIM_API CGizmo : public Component
{
public:

};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentGizmo_h__
