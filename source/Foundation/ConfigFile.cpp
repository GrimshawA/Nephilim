#include <Nephilim/Foundation/ConfigFile.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/TextStream.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/StringList.h>

#include <cctype>

NEPHILIM_NS_BEGIN

/// Just initialize the structure
ConfigFile::ConfigFile()
{

}

/// Release everything
ConfigFile::~ConfigFile()
{

}

/// Load a config file into memory
bool ConfigFile::loadFromFile(const String& filename)
{
	// Iterating a memory buffer is faster than parsing the file itself char by char
	// So we fetch a full string of it, process it and store data

	File file(filename, IODevice::TextRead);
	if (file)
	{
		String file_buffer;

		while (!file.atEnd())
		{
			file_buffer += file.getChar();
		}
		// Make sure it ends in a \n
		if (file_buffer[file_buffer.size() - 1] != '\n')
		{
			file_buffer += "\n";
		}

		// Now do the parsing on the buffer, in one pass
		bool _LineIdentified = false;
		bool _InObjectTag = false;
		bool _InProperty = false;
		String _TempObject;
		String _Property;
		ObjectData* _Object = nullptr;
		for (std::size_t i = 0; i < file_buffer.size(); ++i)
		{
			if (file_buffer[i] != '\r')
			{
				if (file_buffer[i] == '\n')
				{
					// Line ended, Commit the property
					if (_InProperty)
					{
						if (_Object)
						{
							String prop;
							String val;

							StringList params = _Property.split('=');
							if (params.size() == 2)
							{
								prop = params[0];
								val = params[1];

								prop.trim();
								val.trim();
							}

							_Object->members.push_back(prop);
							_Object->values.push_back(val);
						}

						_Property.clear();
					}

					_InObjectTag = false;
					_InProperty = false;
					_LineIdentified = false;

				}
				else if (!_LineIdentified && file_buffer[i] == '[')
				{
					_InObjectTag = true;
					_LineIdentified = true;
				}
				else if (_LineIdentified && _InObjectTag && file_buffer[i] == ']')
				{
					_InObjectTag = false;
					_LineIdentified = false;

					// Commit the new object
					ObjectData objectData;
					objectData.name = _TempObject;
					objects.push_back(objectData);
					_Object = getObject(objectData.name);

					Log("COMMIT OBJECT: %s", _TempObject.c_str());
					_TempObject.clear();
				}
				else if (_LineIdentified && _InObjectTag)
				{
					_TempObject += file_buffer[i];
				}
				else if (!_LineIdentified && std::isalpha(file_buffer[i]))
				{
					_LineIdentified = true;
					_InProperty = true;

					_Property += file_buffer[i];
				}
				else if (_LineIdentified && _InProperty)
				{
					_Property += file_buffer[i];
				}
			}

		}

		return true;
	}
	else
		return false;
}

/// Write all objects currently stored in memory to a file
bool ConfigFile::writeToFile(const String& filename)
{
	File file(filename, IODevice::TextWrite);
	if (file)
	{
		TextStream stream(file);

		for (std::size_t i = 0; i < objects.size(); ++i)
		{
			stream << "[" + objects[i].name + "]\n";
			
			for (std::size_t j = 0; j < objects[i].members.size(); ++j)
			{
				stream << objects[i].members[j] + " = " + objects[i].values[j] +  "\n";
			}

			stream << "\n";
		}

		return true;
	}
	else
	{
		return false;
	}
}

/// Get the reference to the object we want
ConfigFile::ObjectData* ConfigFile::getObject(const String& name)
{
	for (auto& s : objects)
	{
		if (s.name == name)
		{
			return &s;
		}
	}
	return nullptr;
}

NEPHILIM_NS_END