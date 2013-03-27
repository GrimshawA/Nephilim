/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef PARABOLA_KINESISDEBUGDRAW_H
#define PARABOLA_KINESISDEBUGDRAW_H

#include "Platform.h"
//#include "Drawable.h"
#include <Box2D/Box2D.h>

struct b2AABB;
PARABOLA_NAMESPACE_BEGIN

class KinesisWorld;
class Renderer;

/**
	\ingroup Kinesis
	\class KinesisDebugDraw
	\brief A debug renderer to draw a Kinesis simulation.
*/
class PARABOLA_API KinesisDebugDraw : public b2Draw
{
public:
	KinesisDebugDraw();

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	void DrawTransform(const b2Transform& xf);

	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

	void DrawString(int x, int y, const char* string, ...); 

	void DrawAABB(b2AABB* aabb, const b2Color& color);

private:
	friend class KinesisWorld;

	float PixelsPerMeter;
	KinesisWorld* myParent;
	Renderer* renderer;

//	sf::RenderTarget *myTarget;
};

PARABOLA_NAMESPACE_END
#endif

