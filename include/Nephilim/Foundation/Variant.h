#ifndef NephilimFoundationVariant_h__
#define NephilimFoundationVariant_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

/**
	\class Variant
	\brief A variable that can hold different types seamlessly
*/
class NEPHILIM_API Variant
{
public:

	/// An invalid variant that defines no value at all
	static Variant Invalid;

	enum Type
	{
		_Int,     ///< int
		_String,  ///< String
		_Float,   ///< float
		_Double,  ///< double
		_Vector2D,///< Vector2D (float)
		_Vector3D,///< Vector3D (float)
		_Vector4D,///< Vector4D (float)
		_Bool,    ///< bool
	};


private:
	
	/// Struct for Vector4D's, no need additional ones for other vecs
	struct _vecf
	{
		float x;
		float y;
		float z;
		float w;
	};

	/// The union for supporting multiple types
	union
	{
		int _intval;
		float _floatval;
		char* _strval;
		_vecf _vecfval;
		bool _boolval;
	};

	/// Current underlying type of this union
	Type type;

public:

	/// Construct null
	Variant();

	/// Construct from a string
	Variant(const String& val);

	/// Construct from a Vector2D of floats
	Variant(const Vector2D& val);

	/// Construct from a Vector3D of floats
	Variant(const Vector3D& val);

	/// Construct from a Vector4D of floats
	Variant(const Vector4D& val);

	/// Construct from a bool
	Variant(const bool& val);

	/// Construct from an integer
	Variant(int val);

	/// Ensure release of resources
	~Variant();

	/// Get the type of the variant as string, for debugging purposes
	String typeName();

	/// Return as string
	String toString();

	/// Return as a bool
	bool toBool();

	/// Return as a Vector2D
	Vector2D toVector2D();

	/// Return as a Vector3D
	Vector3D toVector3D();

	/// Return as a Vector4D
	Vector4D toVector4D();

	/// Return as an integer
	int toInt();
};

NEPHILIM_NS_END
#endif // NephilimFoundationVariant_h__
