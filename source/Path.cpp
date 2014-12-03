#include <Nephilim/Path.h>
#include <Nephilim/Logger.h>

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
	String filename = m_path;
	if(m_path.find_last_of('/') != m_path.npos)
	{
		filename.erase(filename.begin(), filename.begin() + m_path.find_last_of('/') + 1);
	}

	//Log("Result filename from path: %s", filename.c_str());
	return filename;
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