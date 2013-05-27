#ifndef NephilimVectors_h__
#define NephilimVectors_h__

#include "Platform.h"
#include <math.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\class Vec2<T> 
	\brief 2D Vector

	This class defines a bidimensional vector (x,y) and its operations.

	Vec2<float> specialization is typedef'd to vec2 for a cleaner coding style in the common float computations.
*/
template <class T>
class NEPHILIM_API Vec2
{
public:
	/// Creates an uninitialized Vec2
	Vec2();

	/// Creates a Vec2 with initial values
	Vec2(T x, T y);

	/// Get the length of the vector
	float length();

	/// Makes the vector unit-length
	void normalize();

	/// Returns a normalized copy of this vector
	Vec2<T> normalized();
	
	/// Sets all values of the 2D vector
	void set(T x, T y);

	/// Sets all values of the 2D vector as x
	void setAll(T x);

	/// Comparison operator overload
	bool operator==(const Vec2<T> &vec) const;

	/// Comparison operator overload
	bool operator!=(const Vec2<T> &vec) const;

	/// Assignment operator overload
	Vec2<T>& operator+=(const Vec2<T> &vec);
	/// Assignment operator overload
	Vec2<T>& operator+=(const T &scalar);
	/// Assignment operator overload
	Vec2<T>& operator-=(const Vec2<T> &vec);
	/// Assignment operator overload
	Vec2<T>& operator-=(const T &scalar);
	/// Assignment operator overload
	Vec2<T>& operator*=(const Vec2<T> &vec);
	/// Assignment operator overload
	Vec2<T>& operator*=(const T &scalar);
	/// Assignment operator overload
	Vec2<T>& operator/=(const Vec2<T> &vec);
	/// Assignment operator overload
	Vec2<T>& operator/=(const T &scalar);

	/// Addition operator overload that sums with another 3D Vector of the same type.
	Vec2<T> operator+(const Vec2<T> &vec);
	/// Addition operator overload that sums all members with a scalar value
	Vec2<T> operator+(const T &scalar);

	/// Subtraction operator overload that sums with another 3D Vector of the same type.
	Vec2<T> operator-(const Vec2<T> &vec);
	/// Subtraction operator overload that sums all members with a scalar value
	Vec2<T> operator-(const T &scalar);

	/// Multiplication operator overload that sums with another 3D Vector of the same type.
	Vec2<T> operator*(const Vec2<T> &vec);
	/// Multiplication operator overload that sums all members with a scalar value
	Vec2<T> operator*(const T &scalar);

	/// Division operator overload that sums with another 3D Vector of the same type.
	Vec2<T> operator/(const Vec2<T> &vec);
	/// Division operator overload that sums all members with a scalar value
	Vec2<T> operator/(const T &scalar);

	/// Direct accessors
	T x;
	/// Direct accessors
	T y;
};
typedef Vec2<float> vec2;

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec2<double> Vec2d;



/**
	\ingroup Foundation
	\class Vec3<T>
	\brief 3D Vector
*/
template<class T>
class NEPHILIM_API Vec3{
public:
	/// Creates an uninitialized Vec3
	Vec3();

	/// Creates a Vec3 with initial values
	Vec3(T x, T y, T z);

	/// Creates a vec3 from a vec2 and a z value
	Vec3(Vec2<T> val, T z);

	/// Return the first two components as (x,y)
	Vec2<T> xy();

	/// Sets all values of the 3D vector
	void set(T x, T y, T z);

	/// Sets all values of the 3D vector as x
	void setAll(T x);

	/// Get the length of the vector
	float length();

	/// Makes the vector unit-length
	void normalize();

	/// Compute the cross product
	Vec3<T> cross(const Vec3<T> &vec);

	/// Compute the dot product
	float dot(const Vec3<T> &vec);

	/// Comparison operator overload
	bool operator==(const Vec3<T> &vec);
	/// Comparison operator overload
	bool operator!=(const Vec3<T> &vec);

	/// Assignment operator overload
	Vec3<T>& operator+=(const Vec3<T> &vec);
	/// Assignment operator overload
	Vec3<T>& operator+=(const T &scalar);
	/// Assignment operator overload
	Vec3<T>& operator-=(const Vec3<T> &vec);
	/// Assignment operator overload
	Vec3<T>& operator-=(const T &scalar);
	/// Assignment operator overload
	Vec3<T>& operator*=(const Vec3<T> &vec);
	/// Assignment operator overload
	Vec3<T>& operator*=(const T &scalar);
	/// Assignment operator overload
	Vec3<T>& operator/=(const Vec3<T> &vec);
	/// Assignment operator overload
	Vec3<T>& operator/=(const T &scalar);

	/// Addition operator overload that sums with another 3D Vector of the same type.
	Vec3<T> operator+(const Vec3<T> &vec);
	/// Addition operator overload that sums all members with a scalar value
	Vec3<T> operator+(const T &scalar);

	/// Subtraction operator overload that sums with another 3D Vector of the same type.
	Vec3<T> operator-(const Vec3<T> &vec);
	/// Subtraction operator overload that sums all members with a scalar value
	Vec3<T> operator-(const T &scalar);

	/// Multiplication operator overload that sums with another 3D Vector of the same type.
	Vec3<T> operator*(const Vec3<T> &vec);
	/// Multiplication operator overload that sums all members with a scalar value
	Vec3<T> operator*(const T &scalar);

	/// Division operator overload that sums with another 3D Vector of the same type.
	Vec3<T> operator/(const Vec3<T> &vec);
	/// Division operator overload that sums all members with a scalar value
	Vec3<T> operator/(const T &scalar);

	/// Direct accessors
	T x;
	/// Direct accessors
	T y;
	/// Direct accessors
	T z;
};
typedef Vec3<float> vec3;

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
typedef Vec3<double> Vec3d;


/**
	\ingroup Foundation
	\class Vec4<T> 
	\brief 4D Vector
*/
template<class T>
class NEPHILIM_API Vec4{
public:
	/// Creates a zero vector. w component is 1 by default, defining a "position"
	Vec4();

	/// Creates a Vec4 with initial values
	Vec4(T x, T y, T z, T w);

	/// Creates a Vec4 from a Vec3 and a w component
	Vec4(Vec3<T> vec3, T w);

	/// Sets all values of the 4D vector
	void set(T x, T y, T z, T w);

	/// Sets all values of the 4D vector as x
	void setAll(T x);

	/// Get the first three components of the vector
	Vec3<T> xyz();

	/// Get the first two components
	Vec2<T> xy();

	/// Normalize the vector
	void normalize();

	/// Get the length of the vector
	float length();

	/// Cast the vec4 to another type
	template<class N>	Vec4<N> cast();

	/// Comparison operator overload
	bool operator==(const Vec4<T> &vec);
	/// Comparison operator overload
	bool operator!=(const Vec4<T> &vec);

	/// Assignment operator overload
	Vec4<T>& operator+=(const Vec4<T> &vec);
	/// Assignment operator overload
	Vec4<T>& operator+=(const T &scalar);
	/// Assignment operator overload
	Vec4<T>& operator-=(const Vec4<T> &vec);
	/// Assignment operator overload
	Vec4<T>& operator-=(const T &scalar);
	/// Assignment operator overload
	Vec4<T>& operator*=(const Vec4<T> &vec);
	/// Assignment operator overload
	Vec4<T>& operator*=(const T &scalar);
	/// Assignment operator overload
	Vec4<T>& operator/=(const Vec4<T> &vec);
	/// Assignment operator overload
	Vec4<T>& operator/=(const T &scalar);

	/// Addition operator overload that sums with another 4D Vector of the same type.
	Vec4<T> operator+(const Vec4<T> &vec);
	/// Addition operator overload that sums all members with a scalar value
	Vec4<T> operator+(const T &scalar);
	
	/// Subtraction operator overload that sums with another 4D Vector of the same type.
	Vec4<T> operator-(const Vec4<T> &vec);
	/// Subtraction operator overload that sums all members with a scalar value
	Vec4<T> operator-(const T &scalar);

	/// Multiplication operator overload that sums with another 4D Vector of the same type.
	Vec4<T> operator*(const Vec4<T> &vec);
	/// Multiplication operator overload that sums all members with a scalar value
	Vec4<T> operator*(const T &scalar);

	/// Division operator overload that sums with another 4D Vector of the same type.
	Vec4<T> operator/(const Vec4<T> &vec);
	/// Division operator overload that sums all members with a scalar value
	Vec4<T> operator/(const T &scalar);

	/// Direct accessors
	T x;
	/// Direct accessors
	T y;
	/// Direct accessors
	T z;
	/// Direct accessors
	T w;
};
typedef Vec4<float> vec4;

typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;
typedef Vec4<double> Vec4d;

/// Inline definitions
#include "Vectors.inl"

NEPHILIM_NS_END
#endif // NephilimVectors_h__