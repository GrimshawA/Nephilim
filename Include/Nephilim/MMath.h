#ifndef PARABOLA_MATH_H
#define PARABOLA_MATH_H

#include "Platform.h"
#include "Vectors.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Foundation
	\namespace Math
	\brief Contains useful math functions and constants to help in common game development tasks
*/

namespace Math{

	/// The pi constant - 3.1415926
	extern double pi;


	/// Compute the distance between two points.
	/// Takes two 2D Vectors of type float and returns float
	PARABOLA_API float distance(const Vec2f &a, const Vec2f &b);
	/// Compute the distance between two points.
	/// Takes the coordinates of two points (x1,y1) and (x2,y2) of type float
	/// \return distance value of type float
	PARABOLA_API float distance(float x1, float y1, float x2, float y2);
	/// Compute the distance between two points.
	/// Takes two 2D Vectors of type double and returns double
	PARABOLA_API double distance(const Vec2d &a, const Vec2d &b);
	/// Compute the distance between two points.
	/// Takes the coordinates of two points (x1,y1) and (x2,y2) of type double
	/// \return distance value of type double
	PARABOLA_API double distance(double x1, double y1, double x2, double y2);
	/// Compute the distance between two points.
	/// Takes two 2D Vectors of type int and returns int, possibly truncated if the distance is not integer valued
	PARABOLA_API int distance(const Vec2i &a, const Vec2i &b);
	/// Compute the distance between two points.
	/// Takes the coordinates of two points (x1,y1) and (x2,y2) of type int
	/// \return distance value of type int
	PARABOLA_API int distance(int x1, int y1, int x2, int y2);


	/// Computes a random number between min and max - type double
	PARABOLA_API double random(double min, double max);
	/// Computes a random number between min and max - type int
	PARABOLA_API int randomInt(int min, int max);

	/// Computes the radian angle between two points (x1,y1) and (x2,y2)
	PARABOLA_API double computeAngle(int x1, int y1, int x2, int y2);

	/// Computes the angle between two positions
	PARABOLA_API float computeAngle(const Vec2f &x, const Vec2f &y);

	/// Computes the radian angle between two points (x1,y1) and (x2,y2)
	PARABOLA_API double computeAngle(float x1, float y1, float x2, float y2);


	/**
		\brief Converts an angle in degrees to radians

		Recommended use as degreeToRadian<double>(angle) for type compatibility with other functions.
	*/
	template<class T>
	T degreeToRadian(T degree){
		T radian = 0;
		radian = degree * (pi/180);
		return radian;
	}

	/**
		\brief Converts an angle in radians to degrees

		Recommended use as radianToDegree<double>(angle) for type compatibility with other functions.
	*/
	template<class T>
	T radianToDegree(T radian){
		T degree = 0.0f;
		degree = radian * (180.f/pi);
		return degree;
	}

	// He

};
PARABOLA_NAMESPACE_END

#endif