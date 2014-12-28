#ifndef NephilimCamera_h__
#define NephilimCamera_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Vectors.h>
#include <Nephilim/Math/Matrix.h>
#include <Nephilim/World/CCameraLens.h>
#include <Nephilim/World/CTransform.h>

NEPHILIM_NS_BEGIN

/**
	\class Camera
	\brief This class holds a complete camera information (transform + lens)
*/
class NEPHILIM_API Camera
{
public:
	CTransform transform;
	CCameraLens lens;
};

NEPHILIM_NS_END
#endif // NephilimCamera_h__
