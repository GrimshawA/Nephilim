#ifndef NephilimFoundationFileSystemModel_h__
#define NephilimFoundationFileSystemModel_h__

#include <Nephilim/Foundation/DataModel.h>
#include <Nephilim/Foundation/Path.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class FileSystemModel
	\brief Dataset with local file system information

	Optionally also tracks down changes in real time.

	Put simply, this has a table of data about the file system,
	where there is one row per directory and per file.

	This model is made by 4 columns:
	[0] = name
	[1] = isFile boolean
	[2] = full path
	[3] = parent row
*/
class NEPHILIM_API FileSystemModel : public DataModel
{
private:

	/// The root directory this file system 
	String _rootDirectory;

	/// Do the full regeneration of the model
	void regenerate();

	std::vector<Path> _data;

	/// File system item - directory or file
	struct FSItem
	{
		bool isFile;
		String fileName;
		Path fullPath;         ///< Every file system item has a Path to manipulate it
		int parentRow; /// can only index files to directories
	};

	/// The data on this model
	std::vector<FSItem> items;

public:

	/// Construct the model in invalid state
	FileSystemModel();

	/// Construct the model from an actual directory
	FileSystemModel(const String& rootDirectory);

	/// Find which row index parents the given filename (forcefully a directory or root)
	int getParentOfFile(const String& filename);

	/// Get the data at a given location
	virtual Variant data(int row, int column);

	/// Get the number of rows
	virtual int rows();
};

NEPHILIM_NS_END
#endif // NephilimFoundationFileSystemModel_h__
