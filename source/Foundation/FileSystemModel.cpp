#include <Nephilim/Foundation/FileSystemModel.h>
#include <Nephilim/Foundation/FileSystem.h>
#include <Nephilim/Foundation/Logging.h>

#include <set>

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
/// LIMITATION: DOESN'T GET EMPTY DIRECTORIES YET
void FileSystemModel::regenerate()
{
	std::set<String> directories;

	if (!_rootDirectory.empty())
	{
		StringList fileList = FileSystem::scanDirectory(_rootDirectory, "*", true);

		// Extract all directories
		for (auto s : fileList)
		{
			Path p(s);

			String dirOnly = p.getDirectory();
			directories.insert(dirOnly);
		}

		for (auto s : fileList)
		{
			Path p(s);

			_data.push_back(p);

			Log("File %s", p.m_path.c_str());
		}
	}

	// Unique directories
	for (auto dir : directories)
	{
		Log("Unique directory: %s", dir.c_str());
		Log("For short: %s", Path(dir).getFileName().c_str());

		Path dirPath(dir);
		dirPath.makeRelativeTo(Path(_rootDirectory));

		if (dirPath.get().size() > 0)
		{
			FSItem item;
			item.parentRow = 0;
			item.fileName = Path(dir).getFileName();
			item.isFile = false;
			item.fullPath = dirPath;
			items.push_back(item);
		}
	}

	// Files are unique by themselves, add all and parent them
	for (auto f : _data)
	{
		FSItem item;
		item.parentRow = 0;
		item.fileName = Path(f).getFileName();
		item.isFile = true;
		item.fullPath = f;
		item.fullPath.makeRelativeTo(Path(_rootDirectory));
		items.push_back(item);
	}

	// Subtract the root directory, its important to keep all files relative to it for any usable purposes
	for (auto& item : items)
	{			

		if (item.isFile)
		{
			item.parentRow = getParentOfFile(item.fullPath.get());
			Log("Final item entry %s parent [%d]", item.fullPath.get().c_str(), item.parentRow);
		}
		else
		{
			item.parentRow = -1; // for now no recursive directories
			Log("Final item entry %s parent [%d]", item.fullPath.get().c_str(), item.parentRow);
		}
	}
}

/// Find which row index parents the given filename (forcefully a directory or root)
int FileSystemModel::getParentOfFile(const String& filename)
{
	// We don't even have a parent row, return -1, that means the file stays at root
	if (Path(filename).isNameOnly())
	{
		return -1;
	}
	
	int i = 0;
	for (auto item : items)
	{
		// only care to compare about directories
		if (!item.isFile)
		{
			if (item.fullPath.isParentOf(filename))
				return i;
		}

		++i;
	}

	/// Error, we couldn't parent to anything for some reason, this can't happen
	return -2;
}

/// Get the data at a given location
Variant FileSystemModel::data(int row, int column)
{
	if (column == 0)
	{
		return Variant(items[row].fileName);
	}
	else if (column == 1)
	{
		return Variant(items[row].isFile);
	}
	else if (column == 2)
	{
		return Variant(items[row].fullPath.get());
	}
	else if (column == 3)
	{
		return Variant(items[row].parentRow);
	}
	else
	{
		return Variant::Invalid;
	}
}

/// Get the number of rows
int FileSystemModel::rows()
{
	return _data.size();
}

NEPHILIM_NS_END