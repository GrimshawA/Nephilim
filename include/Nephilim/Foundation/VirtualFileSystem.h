#ifndef NephilimVirtualFS_h__
#define NephilimVirtualFS_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class VirtualFileSystem
	\brief An emulated file system to help manage game resources

	This virtual file system is basically a database of files and directories.
	Its job to translate virtual game resources into actual files, directories,
	files within packages and even from network.

	This is just an abstraction to hide away the real file system, for a truly
	portable way to reference assets.
*/
class NEPHILIM_API VirtualFileSystem
{
public:

	void indexSearchPath(const String& realPath, const String& indexAt);
	
	/// Check if a given file exists
	bool exists(const String& filename);

	/// Translate a virtual to real path
	String translate(const String& filename);

	class IndexedDirectory
	{
	public:
		String realDirectory;
		String indexLocation;
	};

	/// There is a ordered list of indexed locations
	std::vector<IndexedDirectory> indexedDirectories;
	typedef std::vector<IndexedDirectory>::iterator IndexLocationIterator;

};

NEPHILIM_NS_END
#endif // NephilimVirtualFS_h__
