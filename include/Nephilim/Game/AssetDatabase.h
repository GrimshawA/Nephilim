#ifndef NephilimAssetDatabase_h__
#define NephilimAssetDatabase_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Package.h>

NEPHILIM_NS_BEGIN

/**
	\class AssetDatabase
	\brief Information about the assets this game can use
*/
class NEPHILIM_API AssetDatabase
{
public:

	/// Get the package that contains the asset
	/// Returns nullptr if the asset isn't in a known package
	Package* getAssetPackage(const String& asset);
};

NEPHILIM_NS_END
#endif // NephilimAssetDatabase_h__
