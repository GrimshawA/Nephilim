#ifndef PARABOLA3DVIEW_H
#define PARABOLA3DVIEW_H

#include "Platform.h"
#include "Vectors.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API View3D{
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

PARABOLA_NAMESPACE_END
#endif