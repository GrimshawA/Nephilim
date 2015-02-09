#ifndef NephilimFoundationVariant_h__
#define NephilimFoundationVariant_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class Variant
	\brief A variable that can hold different types seamlessly
*/
class NEPHILIM_API Variant
{
private:
	

	union
	{
		int _intval;
		float _floatval;
		char* _strval;
	};

public:

	/// An invalid variant that defines no value at all
	static Variant Invalid;

	enum Type
	{
		_Int,
		_String,
		_Float
	};

	Type type;

public:

	/// Construct null
	Variant();

	/// Construct from a string
	Variant(const String& val);

	/// Construct from an integer
	Variant(int val);

	/// Ensure release of resources
	~Variant();

	/// Get the type of the variant as string, for debugging purposes
	String typeName();

	/// Return as string
	String toString();

	/// Return as an integer
	int toInt();
};

NEPHILIM_NS_END
#endif // NephilimFoundationVariant_h__
