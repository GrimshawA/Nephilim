#include "Nephilim/MMath.h"
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
};

vec3 directionFromAngles(float x_angle, float y_angle)
{
	vec3 direction = vec3(-sin(x_angle),sin(y_angle), cos(x_angle));
	direction.normalize();
	return direction * -1;
}

NEPHILIM_NS_END