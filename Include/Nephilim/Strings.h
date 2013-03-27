#ifndef PARABOLA_STRINGS_H
#define PARABOLA_STRINGS_H

#include "Platform.h"
#include <string>

PARABOLA_NAMESPACE_BEGIN

class StringList;

/**
	\ingroup Foundation
	\class String
	\brief Extension to std::string

	Intended for the common char-based string uses. It provides the standard library tools plus additional ones.

	Note that this is not meant to be used for internationalization of your games.

	Useful things you can do with these strings:

		- Splitting by a delimiter
		- Converting case
		- Converting to other types
*/
class PARABOLA_API String: public std::string{
public:
	/// Content is initialized to an empty string.
	String();
	/// Content is initialized to a copy of the string object str.
	String(const String& str);
	/// Content is initialized to a copy of a substring of str. The substring is the portion of str that begins at the character position pos and takes up to n characters (it takes less than n if the end of str is reached before).
	String(const String& str, size_t pos, size_t n = npos);
	/// Content is initialized to a copy of the string formed by the first n characters in the array of characters pointed by s.
	String(const char * s, size_t n);
	/// Content is initialized to a copy of the string formed by the null-terminated character sequence (C string) pointed by s.
	String(const char * s);
	/// Content is initialized as a string formed by a repetition of character c, n times.
	String(size_t n, char c);
	/// Content is initialized from a std::string
	String(const std::string &s);

	/// Replaces all occurrences of a character
	void replaceCharacter(char replace, char with);
			
	/// Removes characters from beginning until it finds an occurrence of c.			
	void removeUntil(char c);

	/// Removes characters from end until it finds an occurrence of c.			
	void removeUntilReverse(char c);

	/// Remove all occurrences of c 
	void removeCharacter(char c);

	/// Convert to integer
	int toInt();

	/// Convert to float
	float toFloat();

	/// Convert to double
	double toDouble();

	/// Convert to a boolean. Returns true if the string equals "true", case-insensitive and false otherwise.
	bool toBoolean();

	/// Convert the string into lower case
	void toLowerCase();

	/// Splits into a StringList, by the string splitBy.
	StringList split(String splitBy, int limitCount = 0);

	/// Splits into a StringList by the character c.
	StringList split(char c, int limitCount = 0);

	/// Checks if the string starts with str
	bool startsWith(const String &str);

	/// Check if the string ends with str
	/// untested
	bool endsWith(const String &str);

	/// Checks if the string contains str somewhere in it
	bool contains(const String &str);

	/// Implicit conversion to const char* with c_str()
	operator const char*();

	/// Overload for operator=
	String& operator=(const std::string &str);

	/// Overload for operator= for const char*
	String& operator=(const char* c);

	/// Overload of operator+=
	String& operator+=(const String &str);

	/// Overload of operator+= for char types
	String& operator+=(char c);

	/// Overload of operator+
	const String operator+(const String &str) const;

	/// Overload of operator+ for const char *
	const String operator+(const char* c) const;

	/// Overload for operator[] for int literals - set operator
	const char& operator[](int pos) const;

	/// Overload for operator[] for int literals - get operator
	char& operator[](int pos);




	/// Creates a string from an int
	static String number(int n);

	/// Creates a string from an unsigned int
	static String number(unsigned int n);

	/// Creates a string from a float
	static String number(float n);

	/// Creates a string from a double
	static String number(double n);

	/// Creates a string from a long
	static String number(long n);

	/// Creates a string from an unsigned long
	static String number(unsigned long n);

private:
	/// Splits
	void split(String s, char delim, StringList &elems);

};

PARABOLA_NAMESPACE_END
#endif
