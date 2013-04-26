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

#include "Nephilim/KinesisDebugDraw.h"
#include "Nephilim/KinesisWorld.h"
#include "Nephilim/Renderer.h"

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

	KinesisDebugDraw::KinesisDebugDraw() : b2Draw(){
		uint32 flags = 0;
		flags += 1			* b2Draw::e_shapeBit;
		//flags += 1			* b2Draw::e_jointBit;
		//flags += 1			* b2Draw::e_aabbBit;
		//flags += 1			* b2Draw::e_pairBit;
	//	flags += 1			* b2Draw::e_centerOfMassBit;
		SetFlags(flags);

		myParent = NULL;
		renderer = 0;
	};

	void KinesisDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
	/*	glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINE_LOOP);
		for (int32 i = 0; i < vertexCount; ++i)
		{
			glVertex2f(vertices[i].x*PixelsPerMeter, vertices[i].y*PixelsPerMeter);
		}
		glEnd();*/
		
	}

	void KinesisDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{		
		VertexArray vlist(Render::Primitive::TriangleFan, vertexCount);

		Color finalColor;
		finalColor.r = (color.r * 255) / 1;
		finalColor.g = (color.g * 255) / 1;
		finalColor.b = (color.b * 255) / 1;
		finalColor.a = 150;

		for(int i = 0; i < vertexCount; i++){
			vlist[i].position.x = myParent->ToPixels(vertices[i].x);
			vlist[i].position.y = myParent->ToPixels(vertices[i].y);
			vlist[i].color = finalColor;
		}

		renderer->draw(vlist);
	}

	void KinesisDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		/*const float32 k_segments = 16.0f;
		const float32 k_increment = 2.0f * b2_pi / k_segments;
		float32 theta = 0.0f;
		glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINE_LOOP);
		for (int32 i = 0; i < k_segments; ++i)
		{
			b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
			glVertex2f(v.x*PixelsPerMeter, v.y*PixelsPerMeter);
			theta += k_increment;
		}
		glEnd();*/
	}

	void KinesisDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		Color finalColor;
		finalColor.r = (color.r * 255) / 1;
		finalColor.g = (color.g * 255) / 1;
		finalColor.b = (color.b * 255) / 1;
		finalColor.a = 150;
		renderer->drawDebugCircle(Vec2f(myParent->ToPixels(center.x), myParent->ToPixels(center.y)), myParent->ToPixels(radius), Vec2f(axis.x, axis.y), finalColor);
	}

	void KinesisDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		/*glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINES);
		glVertex2f(p1.x*PixelsPerMeter, p1.y*PixelsPerMeter);
		glVertex2f(p2.x*PixelsPerMeter, p2.y*PixelsPerMeter);
		glEnd();*/
	}

	void KinesisDebugDraw::DrawTransform(const b2Transform& xf)
	{
		/*b2Vec2 p1 = xf.p, p2;
		const float32 k_axisScale = 0.4f;
		glBegin(GL_LINES);
		
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(p1.x*PixelsPerMeter, p1.y*PixelsPerMeter);
		p2 = p1 + k_axisScale * xf.q.GetXAxis();
		glVertex2f(p2.x*PixelsPerMeter, p2.y*PixelsPerMeter);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(p1.x*PixelsPerMeter, p1.y*PixelsPerMeter);
		p2 = p1 + k_axisScale * xf.q.GetYAxis();
		glVertex2f(p2.x*PixelsPerMeter, p2.y*PixelsPerMeter);

		glEnd();*/
	}

	void KinesisDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
	{
		/*glPointSize(size);
		glBegin(GL_POINTS);
		glColor3f(color.r, color.g, color.b);
		glVertex2f(p.x*PixelsPerMeter, p.y*PixelsPerMeter);
		glEnd();
		glPointSize(1.0f);*/
	}

	void KinesisDebugDraw::DrawString(int x, int y, const char *string, ...)
	{
		//renderer->draw(Text(String(string) , x, y));			
	}

	void KinesisDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
	{
		/*glColor3f(c.r, c.g, c.b);
		glBegin(GL_LINE_LOOP); 
		glVertex2f(aabb->lowerBound.x*PixelsPerMeter, aabb->lowerBound.y*PixelsPerMeter);
		glVertex2f(aabb->upperBound.x*PixelsPerMeter, aabb->lowerBound.y*PixelsPerMeter);
		glVertex2f(aabb->upperBound.x*PixelsPerMeter, aabb->upperBound.y*PixelsPerMeter);
		glVertex2f(aabb->lowerBound.x*PixelsPerMeter, aabb->upperBound.y*PixelsPerMeter);
		glEnd();*/
	}

NEPHILIM_NS_END
