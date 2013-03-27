#ifndef PARABOLA_NAMEGENERATOR_H
#define PARABOLA_NAMEGENERATOR_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup SceneGraph
	\class NameGenerator
	\brief Structure to generate unique names

	Really straightforward use. Just create your NameGenerator:

	NameGenerator nameGen("camera");

	Then, it is used by calling generate(), for example:

	nameGen.generate(); // Returns "camera1"
	nameGen.generate(); // Returns "camera2"
	nameGen.generate(); // Returns "camera3"

	Easy enough! 
*/
class PARABOLA_API NameGenerator{
public:
	/// Creates a name generator from a keyword
	NameGenerator(const String &keyword);

	/// Creates a name generator from the empty string keyword.
	/// This means it will only generate strings such as "1","2","3","4","5"
	NameGenerator();

	/// Skips count id's, normally not needed.
	void skipGenerations(int count = 1);

	/// Resets the name generator with the keyword
	void setKeyword(const String &keyword);

	/// Generates the next string formed by keyword+id
	String generate();

private:
	String myKeyword;
	int myNextValid;
};

PARABOLA_NAMESPACE_END
#endif