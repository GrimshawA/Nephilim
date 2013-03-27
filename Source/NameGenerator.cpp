#include "Nephilim/NameGenerator.h"


PARABOLA_NAMESPACE_BEGIN

/// Creates a name generator from a keyword
NameGenerator::NameGenerator(const String &keyword){
	setKeyword(keyword);
};

/// Creates a name generator from the empty string keyword.
/// This means it will only generate strings such as "1","2","3","4","5"
NameGenerator::NameGenerator(){
	setKeyword("");
};


/// Resets the name generator with the keyword
void NameGenerator::setKeyword(const String &keyword){
	myKeyword = keyword;
	myNextValid = 1;
};

/// Skips count id's, normally not needed.
void NameGenerator::skipGenerations(int count){
	myNextValid += count;
};

/// Generates the next string formed by keyword+id
String NameGenerator::generate(){
	return myKeyword + String::number(myNextValid++);
};

PARABOLA_NAMESPACE_END