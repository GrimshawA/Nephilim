#ifndef NephilimMaterial_h__
#define NephilimMaterial_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class Material
	\brief Material definition for the 3D renderer

	A material describes a surface's properties. From the texture, normal maps, colors and many other parameters.

	The shader generator looks at a material definition and uses it to generate an appropriate shader for the given platform.
*/
class NEPHILIM_API Material
{
public:
	float shininess;
	float reflectiveness;
};

NEPHILIM_NS_END
#endif // Material_h__
