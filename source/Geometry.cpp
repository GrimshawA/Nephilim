#include <Nephilim/Geometry.h>
#include <Nephilim/MMath.h>
#include <Nephilim/File.h>
#include <Nephilim/Logger.h>
#include <Nephilim/DataStream.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/CGL.h>

#include <cstring>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

GeometryData::GeometryData()
: m_useColors(true)
, m_useNormals(true)
, m_useTexCoords(true)
{
	m_primitive = Render::Primitive::Triangles;
}

void GeometryData::onDraw(Renderer* renderer)
{
	renderer->enableVertexAttribArray(0);
	if(m_useColors && m_colors.size() > 0) renderer->enableVertexAttribArray(1);
	if(m_useTexCoords && m_texCoords.size() > 0) renderer->enableVertexAttribArray(2);
	if(m_useNormals && m_normals.size() > 0) renderer->enableVertexAttribArray(3);

	renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &m_vertices[0]);
	if(m_useColors && m_colors.size() > 0)       renderer->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &m_colors[0]);
	if(m_useTexCoords && m_texCoords.size() > 0) renderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &m_texCoords[0]);
	if(m_useNormals && m_normals.size() > 0)     renderer->setVertexAttribPointer(3, 3, GL_FLOAT, false, 0, &m_normals[0]);

	renderer->drawArrays(m_primitive, 0, m_vertices.size());

	renderer->disableVertexAttribArray(0);
	if(m_useColors && m_colors.size() > 0) renderer->disableVertexAttribArray(1);
	if(m_useTexCoords && m_texCoords.size() > 0) renderer->disableVertexAttribArray(2);
	if(m_useNormals && m_normals.size() > 0) renderer->disableVertexAttribArray(3);
}


/// Save the geometry to a file in a raw format
bool GeometryData::saveToFile(const String& filename)
{
	File fp(filename, IODevice::BinaryWrite);
	if(fp)
	{
		DataStream writer(fp);

		// write vertices
		writer << m_vertices.size();
		if(m_vertices.size() > 0) fp.write(reinterpret_cast<char*>(&m_vertices[0]), m_vertices.size() * sizeof(vec3));

		// write normals
		writer << m_normals.size();
		if(m_normals.size() > 0) fp.write(reinterpret_cast<char*>(&m_normals[0]), m_normals.size() * sizeof(vec3));

		// write texcoords
		writer << m_texCoords.size();
		if(m_texCoords.size() > 0) fp.write(reinterpret_cast<char*>(&m_texCoords[0]), m_texCoords.size() * sizeof(vec2));

		// write colors
		writer << m_colors.size();
		if(m_colors.size() > 0) fp.write(reinterpret_cast<char*>(&m_colors[0]), m_colors.size() * sizeof(Color));
	}

	return true;
}

/// Load the geometry from a raw format file
bool GeometryData::loadFromFile(const String& filename)
{
	File fp(filename, IODevice::BinaryRead);
	if(fp)
	{
		DataStream reader(fp);

		// read vertices
		Int64 vertexCount;
		reader >> vertexCount;
		m_vertices.resize(vertexCount);
		if(vertexCount > 0) fp.read(reinterpret_cast<char*>(&m_vertices[0]), sizeof(vec3) * vertexCount);

		// read normals
		Int64 normalCount;
		reader >> normalCount;
		m_normals.resize(normalCount);
		if(normalCount> 0) fp.read(reinterpret_cast<char*>(&m_normals[0]), sizeof(vec3) * normalCount);

		// read texcoords
		Int64 texCoordCount;
		reader >> texCoordCount;
		m_texCoords.resize(texCoordCount);
		if(texCoordCount> 0) fp.read(reinterpret_cast<char*>(&m_texCoords[0]), sizeof(vec2) * texCoordCount);

		// read colors
		Int64 colorCount;
		reader >> colorCount;
		m_colors.resize(colorCount);
		if(colorCount> 0) fp.read(reinterpret_cast<char*>(&m_colors[0]), sizeof(Color) * colorCount);

		Log("GeometryData::loadFromFile(%s): Loaded %d vertices", filename.c_str(), vertexCount);
	
	}
	else 
		return false;

	return true;
}

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

	float texcoords[] = {
		0.f,0.f,          1.f,0.f,        1.f,1.f,  0.f,0.f,      1.f, 1.f,          0.f, 1.f, //back face

		1.f,0.f, 0.f,1.f, 0.f,0.f,  1.f,0.f, 1.f,1.f, 0.f, 1.f, //front face

		0.f,0.f,    1.f,0.f    , 1.f,1.f,  1.f,1.f,  0.f,1.f    , 0.f,0.f, //right face

		0.f,0.f, 0.f,1.f ,1.f,0.f,  1.f,1.f , 1.f,0.f, 0.f,1.f, // new left face

		1.f,0.f,   1.f,1.f   , 0.f, 1.f , 0.f,1.f,  0.f,0.f,   1.f,0.f, //bottom

		0.f,0.f ,  0.f,1.f , 1.f,1.f  , 1.f,0.f , 0.f, 0.f  , 1.f,1.f //top
	};

	m_vertices.resize(6 * 6);
	memcpy(&m_vertices[0], vertices, sizeof(float) * 6 * 6 * 3);

	m_texCoords.resize(6*6);
	memcpy(&m_texCoords[0], texcoords, sizeof(float) * 6 * 6 * 2);
	
}

/// Silly plane adding, to be refactored
void GeometryData::addPlane(float width, float depth, float height)
{
	float hx = width / 2.f;
	float hz = depth / 2.f;

	float vertices[] = {
		-hx,height,-hz ,  -hx,height,hz , hx, height, hz   ,  hx,height,-hz  ,-hx, height, -hz  , hx,height,hz //top
	};

	float texcoords[] = 
	{
		0.f,0.f ,  0.f,1.f , 1.f,1.f  , 1.f,0.f , 0.f, 0.f  , 1.f,1.f //top
	};

	m_vertices.resize(6);
	memcpy(&m_vertices[0], vertices, sizeof(float) * 6 * 3);

	m_texCoords.resize(6);
	memcpy(&m_texCoords[0], texcoords, sizeof(float) * 6 * 2);
}

void GeometryData::randomFaceColors()
{
	m_colors.resize(m_vertices.size());
	for(size_t i = 0; i < m_vertices.size(); i += 6)
	{
		Color c(Math::randomInt(0,255), Math::randomInt(0,255), Math::randomInt(0,255));
		m_colors[i] = c;
		m_colors[i+1] = c;
		m_colors[i+2] = c;
		if(i+3 < m_vertices.size())
		{
			m_colors[i+3] = c;
			m_colors[i+4] = c;
			m_colors[i+5] = c;
		}
		
	}
}

void GeometryData::setAllColors(Color color)
{
	m_colors.resize(m_vertices.size());
	for(size_t i = 0; i < m_colors.size(); ++i)
	{
		m_colors[i] = color;
	}
}

void GeometryData::scaleUV(float factor)
{
	for(size_t i = 0; i < m_texCoords.size(); ++i)
	{
		m_texCoords[i].x *= factor;
		m_texCoords[i].y *= factor;
	}
}

void GeometryData::offsetUV(float u, float v)
{
	for(size_t i = 0; i < m_texCoords.size(); ++i)
	{
		m_texCoords[i].x += u;
		m_texCoords[i].y += v;
	}
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