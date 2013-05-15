#ifndef PARABOLA_STRINGLISTS_H
#define PARABOLA_STRINGLISTS_H

#include "Platform.h"
#include "Strings.h"
#include <vector>

NEPHILIM_NS_BEGIN

	/**
			\ingroup Foundation
			\class StringList
			\brief Holds a list of String objects.

			It directly inherits a list<String> and adds functionality, for convenience.
	*/
	class NEPHILIM_API StringList : public std::vector<String>{
		public:
			/// Constructs an empty StringList
			StringList();
			/// Constructs a StringList from another's contents.
			StringList(const StringList &append);

			/// Copy another StringList contents into this one
			void append(const StringList& list);
			/// Copy a String content into a new entry of this list
			void append(const String &str);

			/// Joins all the list entries into a single string, each one separated by delimiter.
			String join(const String &delimiter);
			/// Joins all the list entries into a single string, each one separated by delimiter.
			String join(char delimiter);

	};

NEPHILIM_NS_END
#endif