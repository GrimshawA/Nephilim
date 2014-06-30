#include <Nephilim/VirtualFS.h>
#include <Nephilim/Logger.h>
#include <Nephilim/File.h>
#include <Nephilim/FileSystem.h>

NEPHILIM_NS_BEGIN

void VirtualFS::indexSearchPath(const String& realPath, const String& indexAt)
{
	// Not indexing anything anyway
	if(realPath.size() == 0)
	{
		return;
	}

	IndexedDirectory id;
	id.indexLocation = indexAt;
	id.realDirectory = realPath;
	if(id.realDirectory[id.realDirectory.size()-1] != '/')
		id.realDirectory += '/';
	indexedDirectories.push_back(id);
}

/// Check if a given file exists
bool VirtualFS::exists(const String& filename)
{
	String path = filename.substr(0, filename.find_last_of('/') + 1);
	String file = filename.substr(path.size(), filename.size() - path.size());
	Log("virtual search path: %s", path.c_str());
	Log("virtual file: %s", file.c_str());

	// For each indexed location, from older to newer, lets see if it can be found
	for(IndexLocationIterator it = indexedDirectories.begin(); it != indexedDirectories.end(); ++it)
	{
		Log("Checking for indexed directory %s", it->realDirectory.c_str());
		// Check if this indexed directory is a candidate
		// If the index location of this directory is at the same base level of the requested virtual path
		if(it->indexLocation == path.substr(0, it->indexLocation.size()))
		{
			String fPath = path.substr(1, path.size()-1);

			// how would the requested file look like in the indexed directory?
			String realPathFilename = it->realDirectory + fPath + file;
			Log("Testing for %s", realPathFilename.c_str());
			if(File(realPathFilename, IODevice::BinaryRead))
			{
				Log("I found the file at: %s", realPathFilename.c_str());
				return true;
			}
		}
	}

	return false;
}

/// Translate a virtual to real path
String VirtualFS::translate(const String& filename)
{
	String r;

	String path = filename.substr(0, filename.find_last_of('/') + 1);
	String file = filename.substr(path.size(), filename.size() - path.size());
	Log("virtual search path: %s", path.c_str());
	Log("virtual file: %s", file.c_str());

	// For each indexed location, from older to newer, lets see if it can be found
	for(IndexLocationIterator it = indexedDirectories.begin(); it != indexedDirectories.end(); ++it)
	{
		if(it->indexLocation == path.substr(0, it->indexLocation.size()))
		{
			String fPath = path.substr(1, path.size()-1);

			// how would the requested file look like in the indexed directory?
			String realPathFilename = it->realDirectory + fPath + file;
			Log("Testing for %s", realPathFilename.c_str());
			if(File(realPathFilename, IODevice::BinaryRead))
			{
				Log("I found the file at: %s", realPathFilename.c_str());
				r = realPathFilename;
			}
		}
	}
	return r;
}

NEPHILIM_NS_END