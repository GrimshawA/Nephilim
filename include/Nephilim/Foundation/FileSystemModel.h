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
*/
class NEPHILIM_API FileSystemModel : public DataModel
{
private:

	/// The root directory this file system 
	String _rootDirectory;

	/// Do the full regeneration of the model
	void regenerate();

	std::vector<Path> _data;

public:

	/// Construct the model in invalid state
	FileSystemModel();

	/// Construct the model from an actual directory
	FileSystemModel(const String& rootDirectory);

	/// Get the data at a given location
	virtual Variant data(int row, int column);

	/// Get the number of rows
	virtual int rows();
};

NEPHILIM_NS_END
#endif // NephilimFoundationFileSystemModel_h__
