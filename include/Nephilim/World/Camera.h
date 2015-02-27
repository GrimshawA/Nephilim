#ifndef NephilimCamera_h__
#define NephilimCamera_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/Matrix.h>
#include <Nephilim/Foundation/Transform.h>

#include <Nephilim/World/Components/ACameraComponent.h>

NEPHILIM_NS_BEGIN

/**
	\class Camera
	\brief This class holds a complete camera information (transform + lens)
*/
class NEPHILIM_API Camera
{
public:
	Transform transform;
	ACameraComponent lens;
};

NEPHILIM_NS_END
#endif // NephilimCamera_h__
