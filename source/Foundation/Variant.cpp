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

/// Construct from a Vector2D of floats
Variant::Variant(const Vector2D& val)
{
	type = Variant::_Vector2D;
	_vecfval.x = val.x;
	_vecfval.y = val.y;
}

/// Construct from a Vector3D of floats
Variant::Variant(const Vector3D& val)
{
	type = Variant::_Vector3D;
	_vecfval.x = val.x;
	_vecfval.y = val.y;
	_vecfval.z = val.z;
}

/// Construct from a Vector4D of floats
Variant::Variant(const Vector4D& val)
{
	type = Variant::_Vector4D;
	_vecfval.x = val.x;
	_vecfval.y = val.y;
	_vecfval.z = val.z;
	_vecfval.w = val.w;
}

/// Construct from an integer
Variant::Variant(int val)
{
	_intval = val;
	type = Variant::_Int;
}

/// Construct from a bool
Variant::Variant(const bool& val)
{
	type = Variant::_Bool;
	_boolval = val;
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

/// Return as a bool
bool Variant::toBool()
{
	return _boolval;
}

/// Return as a Vector2D
Vector2D Variant::toVector2D()
{
	return Vector2D(_vecfval.x, _vecfval.y);
}

/// Return as a Vector3D
Vector3D Variant::toVector3D()
{
	return Vector3D(_vecfval.x, _vecfval.y, _vecfval.z);
}

/// Return as a Vector4D
Vector4D Variant::toVector4D()
{
	return Vector4D(_vecfval.x, _vecfval.y, _vecfval.z, _vecfval.w);
}

NEPHILIM_NS_END