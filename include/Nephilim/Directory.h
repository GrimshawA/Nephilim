#ifndef DirectoryPath_h__
#define DirectoryPath_h__

#include "Platform.h"
#include "Strings.h"

NEPHILIM_NS_BEGIN

/**
	\class Path
	\brief A directory or path with utility functions
*/
class NEPHILIM_API Path
{
public:

	/// Get the extension of the file
	/// The '.' is not included; ex: "png", "jpg", "html"
	/// Empty string is returned if there is no extension present
	String getExtension();

	/// Test if the path is relative or absolute
	bool isRelativePath();

	/// The passed path
	String m_path;
};

NEPHILIM_NS_END

#endif // DirectoryPath_h__
