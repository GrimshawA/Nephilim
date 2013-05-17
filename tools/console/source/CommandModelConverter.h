#ifndef CommandModelConverter_h__
#define CommandModelConverter_h__

#include <algorithm>

#include "Command.h"

#include <Nephilim/AssimpConverter.h>
#include <Nephilim/Geometry.h>
using namespace NEPHILIM_NS;

class CommandModelConverter : public NativeCommand
{
public:

	void execute(String command)
	{
		StringList list = command.split(' ');
		if(list.size() > 1)
		{
			AssimpImport import;
			if(import.load(list[1]))
			{
				cout << "Model: " << list[1] << endl;

				GeometryData data;
				AssimpGeometry geometryGenerator(data, import);

				String destination = "mesh.ngx"; // Default destination
				StringList::iterator it = std::find(list.begin(), list.end(), "-o");
				if(it != list.end())
				{
					++it;
					destination = *it;
				}

				data.saveToFile(destination);
			}
			else
			{
				cout << "Are you sure that model is valid? "<< endl;
			}
		}
		else
		{
			cout << "You need to specify a source model." << endl;
		}
		
	}
};

#endif // CommandModelConverter_h__
