#ifndef NephilimPath_h__
#define NephilimPath_h__

#include <Nephilim/Platform.h>
#include "Strings.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\class Path
	\brief A well defined set of operations to deal with files and paths
*/
class NEPHILIM_API Path
{
public:
	Path();

	Path(const String& path);

	void normalizeSlashes();

	/// Returns the file name only without the directory
	String getFileName();

	/// Get the extension of the file
	/// The '.' is not included; ex: "png", "jpg", "html"
	/// Empty string is returned if there is no extension present
	String getExtension();

	/// Test if the path is relative or absolute
	bool isRelativePath();

	String getRelativePathTo(const String& relativeTo);

	/// The passed path
	String m_path;
};

NEPHILIM_NS_END
#endif // NephilimPath_h__
