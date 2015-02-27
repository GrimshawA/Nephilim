#include <Nephilim/Foundation/Path.h>
#include <Nephilim/Foundation/Logging.h>

#ifdef NEPHILIM_WINDOWS
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib") //hack
#endif

NEPHILIM_NS_BEGIN

Path::Path()
{

}

Path::Path(const String& path)
: m_path(path)
{
	normalizeSlashes();
}

/// Makes this path relative to path _p, if applicable
/// Which means this path will only make sense pre appended with _p
void Path::makeRelativeTo(const Path& _p)
{
	m_path.erase(m_path.begin(), m_path.begin() + _p.get().size() + 1);
}

/// Returns true if there is no path pre prending the file name
bool Path::isNameOnly()
{
	return m_path.find('/') == m_path.npos;
}

/// This is called on Path directories to know if a given file is their child
bool Path::isParentOf(const String& _dirOrFile)
{
	if (_dirOrFile.substr(0, m_path.size()) == m_path)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// Just get the path in the form of a string
String Path::get() const
{
	return m_path;
}

/// Get the directory part only, always ending in a '/'
String Path::getDirectory()
{
	return m_path.substr(0, m_path.find_last_of('/')) + "/";
}

void Path::normalizeSlashes()
{
	for (std::size_t i = 0; i < m_path.size(); ++i)
	{
		if (m_path[i] == '\\')
			m_path[i] = '/';
	}
}


/// Returns the file name only without the directory
String Path::getFileName()
{
	// We have a directory, return the dir name
	if (!m_path.empty() && m_path[m_path.size() - 1] == '/')
	{
		String pathCopy = m_path;
		pathCopy.erase(pathCopy.begin() + pathCopy.size()-1);

		if (pathCopy.find_last_of('/') != pathCopy.npos)
		{
			pathCopy.erase(pathCopy.begin(), pathCopy.begin() + pathCopy.find_last_of('/') + 1);
		}

		return pathCopy;
	}
	else
	{
		// We have a file, return the filename.extension

		String filename = m_path;
		if (m_path.find_last_of('/') != m_path.npos)
		{
			filename.erase(filename.begin(), filename.begin() + m_path.find_last_of('/') + 1);
		}

		//Log("Result filename from path: %s", filename.c_str());
		return filename;
	}
}

/// Get the extension of the file
/// The '.' is not included; ex: "png", "jpg", "html"
/// Empty string is returned if there is no extension present
String Path::getExtension()
{
	return m_path.substr(m_path.find_last_of('.')+1, m_path.size()-1);
};

/// Test if the path is relative or absolute
bool Path::isRelativePath()
{
#ifdef NEPHILIM_WINDOWS
	// on windows, special handling
	if(PathIsRelativeA(m_path.c_str())){
		return true;
	}
#else
	// for every other non windows system, the slash defines an absolute path
	if(!m_path.empty() && m_path[0] == '/')
	{
		return true;
	}
#endif
	return false;
};

String Path::getRelativePathTo(const String& relativeTo)
{
	String finalPath = m_path;
	finalPath.erase(finalPath.begin(), finalPath.begin() + relativeTo.size() + 1);
	return finalPath;
}


NEPHILIM_NS_END