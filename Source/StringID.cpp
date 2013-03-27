#include "Nephilim/StringID.h"
#include "Nephilim/CRC32.h"
#include <map>

PARABOLA_NAMESPACE_BEGIN

	
		std::map<StringID, String> StringIDMap;

		StringID makeStringID(const String &Name, bool KeepRecord)
		{
			StringID Hash = CRC32::Instance.CRC((unsigned char*)Name.c_str(), Name.length());

			if(KeepRecord){
				std::map<StringID, String>::iterator it = StringIDMap.find(Hash);

				if(it == StringIDMap.end())
				{
					StringIDMap[Hash] = Name;
				};
			}
			return Hash;
		};

		String getStringFromStringID(StringID ID)
		{
			std::map<StringID, String>::iterator it = StringIDMap.find(ID);

			if(it == StringIDMap.end())
				return String();

			return it->second;
		};
	
PARABOLA_NAMESPACE_END
