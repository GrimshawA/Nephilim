#ifndef NephilimQuaternion_h__
#define NephilimQuaternion_h__

#include "Platform.h"
#include "Matrix.h"

NEPHILIM_NS_BEGIN


class Quaternion
{
public:
	Quaternion();

	Quaternion(float nx, float ny, float nz, float nw);

	void normalize();  

	float x,y,z,w;

	mat4 toMatrix();
	
	static Quaternion fromMatrix(mat4 m);
};

NEPHILIM_NS_END
#endif // NephilimQuaternion_h__
