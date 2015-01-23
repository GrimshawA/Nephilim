#ifndef NephilimNxMath_h__
#define NephilimNxMath_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\namespace math
	\brief Contains useful math functions and constants to help in common game development tasks
*/

namespace math
{

	/// The pi constant - 3.1415926
	extern double pi;


	/// Compute the distance between two points.
	/// Takes two 2D Vectors of type float and returns float
	NEPHILIM_API float distance(const Vec2f &a, const Vec2f &b);
	/// Compute the distance between two points.
	/// Takes the coordinates of two points (x1,y1) and (x2,y2) of type float
	/// \return distance value of type float
	NEPHILIM_API float distance(float x1, float y1, float x2, float y2);
	/// Compute the distance between two points.
	/// Takes two 2D Vectors of type double and returns double
	NEPHILIM_API double distance(const Vec2d &a, const Vec2d &b);
	/// Compute the distance between two points.
	/// Takes the coordinates of two points (x1,y1) and (x2,y2) of type double
	/// \return distance value of type double
	NEPHILIM_API double distance(double x1, double y1, double x2, double y2);
	/// Compute the distance between two points.
	/// Takes two 2D Vectors of type int and returns int, possibly truncated if the distance is not integer valued
	NEPHILIM_API int distance(const Vec2i &a, const Vec2i &b);
	/// Compute the distance between two points.
	/// Takes the coordinates of two points (x1,y1) and (x2,y2) of type int
	/// \return distance value of type int
	NEPHILIM_API int distance(int x1, int y1, int x2, int y2);


	/// Computes a random number between min and max - type double
	NEPHILIM_API double random(double min, double max);
	/// Computes a random number between min and max - type int
	NEPHILIM_API int randomInt(int min, int max);

	/// Computes the radian angle between two points (x1,y1) and (x2,y2)
	NEPHILIM_API double computeAngle(int x1, int y1, int x2, int y2);

	/// Computes the angle between two positions
	NEPHILIM_API float computeAngle(const Vec2f &x, const Vec2f &y);

	/// Computes the radian angle between two points (x1,y1) and (x2,y2)
	NEPHILIM_API double computeAngle(float x1, float y1, float x2, float y2);



	///	\brief Converts an angle in degrees to radians
	template<class T>
	T degreeToRadian(T degree)
	{
		return static_cast<T>(degree * (pi/180));
	}

	
	///	\brief Converts an angle in radians to degrees
	template<class T>
	T radianToDegree(T radian)
	{
		return static_cast<T>(radian * (180.f/pi));
	}


	/// \fn toHomogeneous()
	/// \brief Converts a screen-space coordinate to a homogeneous space coordinate
	/// \param point is the screen-space coordinate we want in homogeneous space
	/// \param left and top are the offset from the top-left corner of the window of the desired target viewport
	vec2 toHomogeneous(vec2i point, int left, int top, int width, int height);

	/**
		\class Angle
		\brief Represents an angle and operations made on them

		Internally represented in radians, provides an interface to convert to other measurement units like degrees, as well as other operations.
	*/
	class NEPHILIM_API Angle
	{
	public:
		/// Defaults to 0, by convention, facing "right"
		Angle();

		/// Initialize the angle with a radian angle
		Angle(float val);

		/// Get as degrees
		float degrees();

		/// Get as radians
		float radians();

		/// Constrain the angle on [0, pi*2]
		void normalize();

		static Angle shortestArc(Angle a, Angle b);

		static Angle fromDegrees(float degree);

	private:
		float value; ///< The internal representation of the angle
	};

	/// Returns v if it is within a and b, otherwise one of the ranges
	float clamp(float a, float b, float v);
};

/**
	\ingroup Foundation
	\class ThresholdRange
	\brief Represents a value and a threshold around it
*/
template<class T>
class NEPHILIM_API ThresholdRange
{
public:
	ThresholdRange(T value, T threshold)
	{
		m_value = value;
		m_threshold = threshold;
	}

	bool operator == (const T& value)
	{
		return ((value >= m_value - m_threshold) && (value <= m_value + m_threshold));
	}

	T m_value;
	T m_threshold;

};


template<class T>
ThresholdRange<T> threshold(T value, T threshold2)
{
	return ThresholdRange<T>(value, threshold2);
}

/// Linear interpolation - Returns a value between A and B depending on the time value, which is in the range [0..1]
template<class T>
T lerp(T A, T B, float time)
{
	return A + (B - A)*time;
}


vec3 directionFromAngles(float x_angle, float y_angle);

NEPHILIM_NS_END
#endif // NephilimNxMath_h__