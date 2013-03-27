#include "Nephilim/StringList.h"

PARABOLA_NAMESPACE_BEGIN

	StringList::StringList(){

	};

	StringList::StringList(const StringList &append) : std::vector<String>(append){

	};


	/// Copy another StringList contents into this one
	void StringList::append(const StringList& list){
		insert(end(), list.begin(), list.end());
	};
	/// Copy a String content into a new entry of this list
	void StringList::append(const String &str){
		insert(end(), str);
	};


	/// Joins all the list entries into a single string, each one separated by delimiter.
	String StringList::join(const String &delimiter){
		String out;
		StringList::const_iterator it = begin();

		while(it != end()){
			out += (*it);
			it++;
			if(it != end())out += delimiter;
		}
		
		return out;
	};
	/// Joins all the list entries into a single string, each one separated by delimiter.
	String StringList::join(char delimiter){
		String out;
		StringList::const_iterator it = begin();

		while(it != end()){
			out += (*it);
			it++;
			if(it != end())out += delimiter;
		}

		return out;
	};

PARABOLA_NAMESPACE_END