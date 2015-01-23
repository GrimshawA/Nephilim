#ifndef NephilimConfigFile_h__
#define NephilimConfigFile_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class ConfigFile
	\brief Write and read .ini style files

	This class can parse and write .ini style files 
	with the following syntax.

	[Text] to define objects
	and then one parameter per line under the object to define properties like
	A = B
*/
class NEPHILIM_API ConfigFile
{
public:

	/// Data for an individual object in the file
	class ObjectData
	{
	public:
		/// Members in this object
		std::vector<String> members;

		/// Values in this object (paired with members)
		std::vector<String> values;

		/// Name of this object
		String name;
	};

	/// Our database of objects
	std::vector<ObjectData> objects;

public:

	/// Just initialize the structure
	ConfigFile();

	/// Release everything
	~ConfigFile();
	
	/// Load a config file into memory
	bool loadFromFile(const String& filename);

	/// Write all objects currently stored in memory to a file
	bool writeToFile(const String& filename);

	/// Get the reference to the object we want
	ObjectData* getObject(const String& name);
};

NEPHILIM_NS_END
#endif // NephilimConfigFile_h__