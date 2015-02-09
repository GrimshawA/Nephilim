#include <Nephilim/Foundation/FileSystemModel.h>
#include <Nephilim/Foundation/FileSystem.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

/// Construct the model in invalid state
FileSystemModel::FileSystemModel()
{

}

/// Construct the model from an actual directory
FileSystemModel::FileSystemModel(const String& rootDirectory)
: _rootDirectory(rootDirectory)
{
	regenerate();
}

/// Do the full regeneration of the model
void FileSystemModel::regenerate()
{
	if (!_rootDirectory.empty())
	{
		StringList fileList = FileSystem::scanDirectory(_rootDirectory, "*", true);
		for (auto s : fileList)
		{
			Path p(s);

			_data.push_back(p);

			Log("File %s", p.m_path.c_str());
		}
	}
}

/// Get the data at a given location
Variant FileSystemModel::data(int row, int column)
{
	return Variant(_data[row].m_path);
}

/// Get the number of rows
int FileSystemModel::rows()
{
	return _data.size();
}

NEPHILIM_NS_END