#ifndef PARABOLA_VECTORS_H
#define PARABOLA_VECTORS_H

#include "Platform.h"
#include <math.h>

PARABOLA_NAMESPACE_BEGIN

	/**
		\ingroup Foundation
		\class Vec2 
		\brief 2D Vector template class

		Provides a 2D vector from any type and defines some operations on it. 
		Logically, if the type passed in is incompatible with the basic operations such as:
			- Comparison
			- Assignment
			- Addition/Subtraction
			- Multiplication/Division

		you will probably get compiler errors.

		For convenience, Vec2i, Vec2f and Vec2d are specializations of Vec2<T>,
		for types int, float and double, respectively.

	*/
	template <class T>
	class PARABOLA_API Vec2{
	public:
		/// Creates an uninitialized Vec2
		Vec2();
		/// Creates a Vec2 with initial values
		Vec2(T x, T y);


		/// Get the length of the vector
		float length();

		/// Makes the vector unit-length
		void normalize();


		/// Sets all values of the 2D vector
		void set(T x, T y);
		/// Sets all values of the 2D vector as x
		void setAll(T x);

		/// Comparison operator overload
		bool operator==(const Vec2<T> &vec);
		/// Comparison operator overload
		bool operator!=(const Vec2<T> &vec);

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


	typedef Vec2<float> Vec2f;
	typedef Vec2<int> Vec2i;
	typedef Vec2<double> Vec2d;



	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
		\ingroup Foundation
		\class Vec3 
		\brief 3D Vector template class

		Provides a 3D vector from any type and defines some operations on it. 
		Logically, if the type passed in is incompatible with the basic operations such as:
			- Comparison
			- Assignment
			- Addition/Subtraction
			- Multiplication/Division

		you will probably get compiler errors.

		For convenience, Vec3i, Vec3f and Vec3d are specializations of Vec3<T>,
		for types int, float and double, respectively.

	*/
	template<class T>
	class PARABOLA_API Vec3{
	public:
		/// Creates an uninitialized Vec3
		Vec3();
		/// Creates a Vec3 with initial values
		Vec3(T x, T y, T z);

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

	typedef Vec3<float> Vec3f;
	typedef Vec3<int> Vec3i;
	typedef Vec3<double> Vec3d;
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
		\ingroup Foundation
		\class Vec4 
		\brief 4D Vector template class

		Provides a 4D vector from any type and defines some operations on it. 
		Logically, if the type passed in is incompatible with the basic operations such as:
			- Comparison
			- Assignment
			- Addition/Subtraction
			- Multiplication/Division

		you will probably get compiler errors.

		For convenience, Vec4i, Vec4f and Vec4d are specializations of Vec4<T>,
		for types int, float and double, respectively.

	*/
	template<class T>
	class PARABOLA_API Vec4{
	public:
		/// Creates an uninitialized Vec4
		Vec4();
		/// Creates a Vec4 with initial values
		Vec4(T x, T y, T z, T w);

		/// Sets all values of the 4D vector
		void set(T x, T y, T z, T w);
		/// Sets all values of the 4D vector as x
		void setAll(T x);

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

	typedef Vec4<float> Vec4f;
	typedef Vec4<int> Vec4i;
	typedef Vec4<double> Vec4d;

	//////////////////////////////////////////////////////////////////////////////////////////////

	#include "Vectors.inl"

PARABOLA_NAMESPACE_END
#endif