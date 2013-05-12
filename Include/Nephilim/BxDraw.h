#ifndef NephilimBxDraw_h__
#define NephilimBxDraw_h__

#include "Platform.h"
#include <LinearMath/btIDebugDraw.h>
#include <Nephilim/Geometry.h>

NEPHILIM_NS_BEGIN

class Renderer;

class NEPHILIM_API BxDraw : public btIDebugDraw
{
public:
	BxDraw();

	void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);

	void drawTriangle(const btVector3 &a, const btVector3 &b, const btVector3 &c, const btVector3 &color, btScalar alpha);
	void drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color);
	void reportErrorWarning(const char *warningString);
	void draw3dText(const btVector3 &location, const char *textString);
	void setDebugMode(int debugMode);
	int getDebugMode() const;
	Renderer* renderer;

	 int debugMode;

	 GeometryData line;
};

NEPHILIM_NS_END
#endif // NephilimBxDraw_h__
