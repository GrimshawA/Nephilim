#ifndef NephilimGraphicsMaterial_h__
#define NephilimGraphicsMaterial_h__

#include <Nephilim/Foundation/Asset.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class Material
	\brief A material asset which objects in the world can instance

	The material is an asset that is loaded from a material definition and then assigned to different
	objects in the world to give them surface detail and color, as well as to help compute lighting.
*/
class NEPHILIM_API Material : public Asset
{
private:

	/// Name of this material
	String name;
};

NEPHILIM_NS_END
#endif // NephilimGraphicsMaterial_h__
