#include <Nephilim/Math/Math.h>
#include <Nephilim/Math/Matrix.h>
#include <stdlib.h>
#include <cmath>

NEPHILIM_NS_BEGIN
namespace math{
		double pi = 3.1415926;/* = atan(1.0)*4*/;

		float distance(const Vec2f &a, const Vec2f &b){
			return ( (float)sqrt(((b.x-a.x)*(b.x-a.x))+((b.y-a.y)*(b.y-a.y))  ) );
		};
		float distance(float x1, float y1, float x2, float y2){
			return ( (float)sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))  ) );
		};

		double distance(const Vec2d &a, const Vec2d &b){
			return (sqrt(((b.x-a.x)*(b.x-a.x))+((b.y-a.y)*(b.y-a.y))  ) );
		};
		double distance(double x1, double y1, double x2, double y2){
			return (sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))  ) );
		};

		int distance(const Vec2i &a, const Vec2i &b){
			return (int)(sqrt((double)((b.x-a.x)*(b.x-a.x))+((b.y-a.y)*(b.y-a.y))  ) );
		};
		int distance(int x1, int y1, int x2, int y2){
			return (int)(sqrt((double)((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))  ) );
		};

		double random(double min, double max){
			double r = (double)rand() / (float)RAND_MAX;
			return min + r * (max - min);
		};

		int randomInt(int min, int max){
			return min + (rand() % (int)(max - min + 1));
		};

		double computeAngle(int x1, int y1, int x2, int y2){
			return atan2((double)(y2 - y1), (double)(x2 - x1));
		};

		double computeAngle(float x1, float y1, float x2, float y2){
			return atan2((y2 - y1), (x2 - x1));
		};

		/// Computes the angle between two positions
		float computeAngle(const Vec2f &x, const Vec2f &y){
			return computeAngle(x.x, x.y, y.x,y.y);
		};

	/// \fn toHomogeneous()
	/// \brief Converts a screen-space coordinate to a homogeneous space coordinate
	/// \param point is the screen-space coordinate we want in homogeneous space
	/// \param left and top are the offset from the top-left corner of the window of the desired target viewport
	vec2 toHomogeneous(vec2i point, int left, int top, int width, int height)
	{
		return vec2(-1.f  + 2.f * (point.x - left)  / width,
					 1.f  - 2.f * (point.y - top)  / height);
	}

////////////////////////////////////////////////////////////////////////// Class Angle

/// Defaults to 0, by convention, facing "right"
Angle::Angle()
: value(0.f)
{
}

/// Initialize the angle with a radian angle
Angle::Angle(float val)
: value(val)
{
}

/// Get as degrees
float Angle::degrees()
{
	return radianToDegree(value);
}

/// Get as radians
float Angle::radians()
{
	return value;
}

/// Constrain the angle on [0, pi*2]
void Angle::normalize()
{
	while(value < 0.f)
	{
		value += pi*2.f;
	}

	while(value > pi*2.f)
	{
		value -= pi*2.f;
	}
}

Angle Angle::shortestArc(Angle a, Angle b)
{
	if (fabs(b.radians()-a.radians()) < math::pi)
		return b.radians()-a.radians();
	if (b.radians()>a.radians())
		return b.radians()-a.radians()-math::pi*2.0f;
	return b.radians()-a.radians()+math::pi*2.0f;
}

Angle Angle::fromDegrees(float degree)
{
	Angle angle;
	angle.value = degreeToRadian(degree);
	return angle;
}

}; // end of namespace math

vec3 directionFromAngles(float x_angle, float y_angle)
{
	/*vec3 direction = vec3(-sin(x_angle),sin(y_angle), cos(x_angle));
	direction.normalize();
	return direction * -1;*/

	vec4 default_front(0,0,-1,0);
	default_front = mat4::rotatey(-x_angle) * default_front;
	default_front = mat4::rotatex(-y_angle) * default_front;
	return default_front.xyz();
}

NEPHILIM_NS_END