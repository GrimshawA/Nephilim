#ifndef PARABOLA3DVIEW_H
#define PARABOLA3DVIEW_H

#include "Platform.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API View3D{
public:
	/// Apply the camera to openGL
	void apply();

	void forward(float amount);
	void backward(float amount);
	void strafe(float amount);
	void rotateH(float amount);

	Vec3f m_eye;
	Vec3f m_center;
	Vec3f m_up;

};

NEPHILIM_NS_END
#endif