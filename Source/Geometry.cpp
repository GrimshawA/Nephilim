#include <Nephilim/Geometry.h>
#include <Nephilim/MMath.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

void GeometryData::addBox(float width, float height, float depth)
{
	float hx = width / 2.f;
	float hy = height / 2.f;
	float hz = depth / 2.f;

	float vertices[] = {
		-hx,-hy,-hz, hx,-hy,-hz, hx,hy,-hz,   -hx,-hy,-hz,  hx,hy,-hz, -hx, hy,-hz, //back face

		hx,-hy,hz, -hx,hy,hz, -hx,-hy,hz,  hx,-hy,hz,  hx,hy,hz, -hx, hy,hz, //front face

		hx,-hy,-hz,    hx,hy,-hz    , hx,hy,hz    ,  hx,hy,hz,  hx,-hy,hz    , 	hx,-hy,-hz, //right face

		-hx,-hy,-hz, - hx,-hy,hz ,-hx,hy,-hz,  - hx,hy,hz ,-hx,hy,-hz,-hx,-hy,hz, // new left face

		hx,-hy,-hz,   hx,-hy,hz    , -hx, -hy, hz   ,  -hx, -hy, hz, - hx,-hy,-hz    , hx,-hy,-hz, //bottom

		-hx,hy,-hz ,  -hx,hy,hz , hx, hy, hz   ,  hx,hy,-hz  ,-hx, hy, -hz  , hx,hy,hz //top
	};

	m_vertices.resize(6 * 6);
	memcpy(&m_vertices[0], vertices, sizeof(float) * 6 * 6 * 3);
}

/// Generates normals for the geometry
void GeometryData::generateNormals()
{
	m_normals.resize(m_vertices.size());
	for(int i = 0; i < m_vertices.size(); i+=3)
	{
		// triangle is m_vertices[i] .. i+1 i+2
		Vec3f normal(0,0,0);

		Vec3f edge1 = m_vertices[i+1] - m_vertices[i];
		Vec3f edge2 = m_vertices[i+2] - m_vertices[i];
		normal = edge1.cross(edge2);
		normal.normalize();

		m_normals[i] = normal;
		m_normals[i+1] = normal;
		m_normals[i+2] = normal;
	}
}


void GeometryData::addCylinder()
{
	float r = 1;
	float h = 5;

	int hg_segments = 5;
	int rd_segments = 100;
	float rd_increment = Math::pi*2 / rd_segments;

	for(int hg = 0; hg < hg_segments; ++hg)
	{
		float height = (-h/2) + (hg+1) * h / hg_segments;
		float pheight = height - h / hg_segments;

		for(int rd = 0; rd < rd_segments; ++rd)
		{
			float theta2 = rd_increment * rd;
			float ptheta2 = theta2 - rd_increment;

			// The 4 points of the quad
			Vec3f p1, p2, p3, p4;
			p1 = Vec3f(cos(theta2) , height, sin(theta2));
			p2 = Vec3f(cos(theta2) , pheight, sin(theta2));
			p3 = Vec3f(cos(ptheta2), height, sin(ptheta2));
			p4 = Vec3f(cos(ptheta2), pheight, sin(ptheta2));

			m_vertices.push_back(p1);
			m_vertices.push_back(p2);
			m_vertices.push_back(p3);

			m_vertices.push_back(p3);
			m_vertices.push_back(p2);
			m_vertices.push_back(p4);
		}
	}

	// top and bottom
	for(int rd = 0; rd < rd_segments; ++rd)
	{
		float theta2 = rd_increment * rd;
		float ptheta2 = theta2 - rd_increment;


		
	}

}

/// Generates the geometry of a torus knot
void GeometryData::addTorusKnot(int p, int q)
{
	int segments = 15000;
	for(float theta = 0.f + Math::pi*2 / segments; theta < Math::pi*2; theta += Math::pi*2 / segments)
	{
		float r = cos(q * theta) + 2;
		Vec3f point(r * cos(p * theta), r * sin(p * theta), -sin(q * theta));
		m_vertices.push_back(point);
	}
}

/// Generates the geometry of a torus knot
void GeometryData::addTorus(int p, int q)
{
	
	float extrusionWidth = 2.f;
	int i_segments = 40;
	for(int i = 0; i < i_segments; ++i)
	{
		float theta = i * Math::pi*2 / i_segments;
		float ptheta = theta - Math::pi*2 / i_segments;

		int k_segments = 4;
		for(int k = 0; k < k_segments; ++k)
		{
			float theta2 = k * Math::pi*2 / k_segments;
			float ptheta2 = theta2 - Math::pi*2 / k_segments;

			// The 4 points of the quad
			Vec3f p1, p2, p3, p4;
			p1 = Vec3f(cos(theta) * (p + cos(theta2)), sin(theta) * (p + cos(theta2)), sin(theta2));
			p2 = Vec3f(cos(ptheta) * (p + cos(theta2)), sin(ptheta) * (p + cos(theta2)), sin(theta2));
			p3 = Vec3f(cos(theta) * (p + cos(ptheta2)), sin(theta) * (p + cos(ptheta2)), sin(ptheta2));
			p4 = Vec3f(cos(ptheta) * (p + cos(ptheta2)), sin(ptheta) * (p + cos(ptheta2)), sin(ptheta2));

			
			m_vertices.push_back(p1);
			m_vertices.push_back(p2);
			m_vertices.push_back(p3);

			m_vertices.push_back(p3);
			m_vertices.push_back(p2);
			m_vertices.push_back(p4);
		}
	}
}

/// Operator overload for adding torus knots
GeometryData& GeometryData::operator<<(const TorusKnotDef& torus)
{
	addTorusKnot(torus.p, torus.q);
	return *this;
}

/// Operator overload for adding torus knots
GeometryData& GeometryData::operator<<(const TorusDef& torus)
{
	addTorus(torus.p, torus.q);
	return *this;
}

Vec3f calculateNormal(Vec3f p1, Vec3f p2, Vec3f p3)
{
	return Vec3f();
}


NEPHILIM_NS_END