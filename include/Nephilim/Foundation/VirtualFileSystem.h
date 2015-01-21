#ifndef NephilimVirtualFS_h__
#define NephilimVirtualFS_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

class NEPHILIM_API VirtualFS
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
