#include <Nephilim/Geometry.h>
#include <Nephilim/MMath.h>

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
	int segments = 30;
	float extrusionWidth = 2.f;

	for(float theta = 0.f + Math::pi*2 / segments; theta < Math::pi*2; theta += Math::pi*2 / segments)
	{
		float ptheta = theta - Math::pi*2 / segments;
		Vec3f point(cos(theta) * p, sin(theta) * p, 0);
		Vec3f point2(cos(ptheta) * p, sin(ptheta) * p, 0);
		m_vertices.push_back(point2);

		// make a face now
		int segs = 40;
		for(float theta2 = 0.f + Math::pi*2 / segs; theta2 < Math::pi*2; theta2 += Math::pi*2 / segs)
		{
			float ptheta2 = theta2 - Math::pi*2 / segs;
			Vec3f v = Vec3f(cos(theta2), sin(theta2), 0);
			m_vertices.push_back(point2 + v.length());

			/*m_vertices.push_back(Vec3f(point.x + cos(ptheta2), point.y + sin(ptheta2), 0));
			m_vertices.push_back(Vec3f(point2.x + cos(theta2), point2.y + sin(theta2), 0));
			m_vertices.push_back(Vec3f(point.x + cos(theta2), point.y + sin(theta2), 0));*/

		/*	m_vertices.push_back(Vec3f(point2.x + cos(theta2), point2.y + sin(theta2), 0));
			m_vertices.push_back(Vec3f(point.x + cos(theta2), point.y + sin(theta2), 0));
			m_vertices.push_back(Vec3f(point.x + cos(ptheta2), point.y + sin(ptheta2), 0));*/
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