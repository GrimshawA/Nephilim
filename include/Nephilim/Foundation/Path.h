#ifndef NephilimFoundationPath_h__
#define NephilimFoundationPath_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class Path
	\brief A well defined set of operations to deal with files and paths
*/
class NEPHILIM_API Path
{
public:
	Path();

	Path(const String& path);

	/// Returns true if there is no path pre prending the file name
	bool isNameOnly();

	/// This is called on Path directories to know if a given file is their child
	bool isParentOf(const String& _dirOrFile);

	/// Just get the path in the form of a string
	String get() const;

	/// Makes this path relative to path _p, if applicable
	/// Which means this path will only make sense pre appended with _p
	void makeRelativeTo(const Path& _p);

	void normalizeSlashes();

	/// Returns the file name only without the directory
	String getFileName();

	/// Get the directory part only, always ending in a '/'
	String getDirectory();

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
#endif // NephilimFoundationPath_h__
