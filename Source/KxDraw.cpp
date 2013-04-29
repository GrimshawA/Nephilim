#include <Nephilim/KxDraw.h>
#include <Nephilim/KxScene.h>

#include "Nephilim/Renderer.h"

#include <Box2D/Box2D.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// The debug drawing
class KxDebugDraw : public b2Draw
{
public:
	KxDebugDraw() : b2Draw()	{}

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	void DrawTransform(const b2Transform& xf);

	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

	void DrawString(int x, int y, const char* string, ...); 

	void DrawAABB(b2AABB* aabb, const b2Color& color);

	KxScene *myParent;
	Renderer* renderer;
};



KxDraw::KxDraw()
: m_scene(NULL)
{

}

KxDraw::KxDraw(KxScene& scene)
: m_scene(&scene)
, m_pixelsPerMeter(scene.getPixelRatio())
{
	
}

void KxDraw::setScene(KxScene& scene)
{
	m_scene = &scene;
	m_pixelsPerMeter = scene.getPixelRatio();
}

KxScene* KxDraw::getScene()
{
	return m_scene;
}

void KxDraw::onDraw(Renderer* renderer)
{
	if(m_scene)
	{
		uint32 flags = 0;
		flags += 1			* b2Draw::e_shapeBit;
		//flags += 1			* b2Draw::e_jointBit;
		//flags += 1			* b2Draw::e_aabbBit;
		//flags += 1			* b2Draw::e_pairBit;
		//flags += 1			* b2Draw::e_centerOfMassBit;

		KxDebugDraw painter;
		painter.SetFlags(flags);
		m_scene->get()->SetDebugDraw(&painter);
		painter.renderer = renderer;
		painter.myParent = m_scene;
		m_scene->get()->DrawDebugData();
	}
}






void KxDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	/*	glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINE_LOOP);
		for (int32 i = 0; i < vertexCount; ++i)
		{
			glVertex2f(vertices[i].x*PixelsPerMeter, vertices[i].y*PixelsPerMeter);
		}
		glEnd();*/
		
}

void KxDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{		
		VertexArray vlist(Render::Primitive::TriangleFan, vertexCount);

		Color finalColor;
		finalColor.r = (color.r * 255) / 1;
		finalColor.g = (color.g * 255) / 1;
		finalColor.b = (color.b * 255) / 1;
		finalColor.a = 150;

		for(int i = 0; i < vertexCount; i++){
			vlist[i].position.x = myParent->toPixels(vertices[i].x);
			vlist[i].position.y = myParent->toPixels(vertices[i].y);
			vlist[i].color = finalColor;
		}

		renderer->draw(vlist);
	}

	void KxDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
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

	void KxDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		Color finalColor;
		finalColor.r = (color.r * 255) / 1;
		finalColor.g = (color.g * 255) / 1;
		finalColor.b = (color.b * 255) / 1;
		finalColor.a = 150;
		renderer->drawDebugCircle(Vec2f(myParent->toPixels(center.x), myParent->toPixels(center.y)), myParent->toPixels(radius), Vec2f(axis.x, axis.y), finalColor);
	}

	void KxDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		/*glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINES);
		glVertex2f(p1.x*PixelsPerMeter, p1.y*PixelsPerMeter);
		glVertex2f(p2.x*PixelsPerMeter, p2.y*PixelsPerMeter);
		glEnd();*/
	}

	void KxDebugDraw::DrawTransform(const b2Transform& xf)
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

	void KxDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
	{
		/*glPointSize(size);
		glBegin(GL_POINTS);
		glColor3f(color.r, color.g, color.b);
		glVertex2f(p.x*PixelsPerMeter, p.y*PixelsPerMeter);
		glEnd();
		glPointSize(1.0f);*/
	}

	void KxDebugDraw::DrawString(int x, int y, const char *string, ...)
	{
		//renderer->draw(Text(String(string) , x, y));			
	}

	void KxDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
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
