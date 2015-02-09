#include <Nephilim/Foundation/Variant.h>

NEPHILIM_NS_BEGIN

/// An invalid variant that defines no value at all
Variant Variant::Invalid;

/// Construct null
Variant::Variant()
{

}

/// Construct from a string
Variant::Variant(const String& val)
{
	_strval = new char[val.size() + 1];
	memcpy(static_cast<void*>(_strval), val.c_str(), val.size());
	_strval[val.size()] = '\0';

	type = Variant::_String;
}

/// Construct from an integer
Variant::Variant(int val)
{
	_intval = val;
	type = Variant::_Int;
}

/// Ensure release of resources
Variant::~Variant()
{
	if (type == Variant::_String)
	{
		delete[] _strval;
	}
}

/// Get the type of the variant as string, for debugging purposes
String Variant::typeName()
{
	return "int";
}

/// Return as string
String Variant::toString()
{
	return String(_strval);
}

/// Return as an integer
int Variant::toInt()
{
	return _intval;
}

NEPHILIM_NS_END