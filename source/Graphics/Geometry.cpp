#include <Nephilim/Graphics/Geometry.h>
#include <Nephilim/Foundation/Math.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/DataStream.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/GL/GLHelpers.h>

#include <cstring>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Generate a plane with center in origin, facing its normal direction, with given dimensions
Geometry Geometry::GeneratePlane(Vector3D origin, Vector3D normal, Vector2D dimensions)
{
	Geometry geom;
	/*
	geom._positions.resize(4);
	geom._positions[0] = Vector3D(10.f, 10.f, -10.f);
	geom._positions[1] = Vector3D(10.f, 10.f, 10.f);
	geom._positions[2] = Vector3D(-10.f, 10.f, 10.f);
	geom._positions[3] = Vector3D(-10.f, 10.f, -10.f);

	geom._colors.resize(4);
	geom._colors[0] = vec4(1.f, 1.f, 1.f, 1.f);
	geom._colors[1] = vec4(1.f, 1.f, 1.f, 1.f);
	geom._colors[2] = vec4(1.f, 1.f, 1.f, 1.f);
	geom._colors[3] = vec4(1.f, 1.f, 1.f, 1.f);

	geom._texcoord.resize(4);
	geom._texcoord[0] = vec2(1.f, 1.f);
	geom._texcoord[1] = vec2(0.f, 1.f);
	geom._texcoord[2] = vec2(0.f, 0.f);
	geom._texcoord[3] = vec2(1.f, 0.f);

	geom._faces.resize(2);
	geom._faces[0].v1 = 0;
	geom._faces[0].v2 = 1;
	geom._faces[0].v3 = 2;
	geom._faces[1].v1 = 0;
	geom._faces[1].v2 = 2;
	geom._faces[1].v3 = 3;
	*/
	return geom;
}

/// Generate a sky box mesh
Geometry Geometry::GenerateSkyBox()
{
	Geometry geom;
	/*
	geom._positions.resize(4);
	geom._faces.resize(2);
	geom._colors.resize(4);
	geom._texcoord.resize(4);

	geom._positions[0] = Vector3D(10.f, 10.f, -10.f);
	geom._positions[1] = Vector3D(10.f, 10.f, 10.f);
	geom._positions[2] = Vector3D(-10.f, 10.f, 10.f);
	geom._positions[3] = Vector3D(-10.f, 10.f, -10.f);

	geom._colors[0] = vec4(1.f, 1.f, 1.f, 1.f);
	geom._colors[1] = vec4(1.f, 1.f, 1.f, 1.f);
	geom._colors[2] = vec4(1.f, 1.f, 1.f, 1.f);
	geom._colors[3] = vec4(1.f, 1.f, 1.f, 1.f);

	geom._texcoord[0] = vec2(1.f, 1.f);
	geom._texcoord[1] = vec2(0.f, 1.f);
	geom._texcoord[2] = vec2(0.f, 0.f);
	geom._texcoord[3] = vec2(1.f, 0.f);

	geom._faces[0].v1 = 0;
	geom._faces[0].v2 = 1;
	geom._faces[0].v3 = 2;
	geom._faces[1].v1 = 0;
	geom._faces[1].v2 = 2;
	geom._faces[1].v3 = 3;
	*/
	return geom;
}

//////////////////////////////////////////////////////////////////////////

/// Merges two meshes into one appropriately
GeometryObject GeometryObject::Merge(const GeometryObject& A, const GeometryObject& B)
{
	GeometryObject C;
	return C;
}

//////////////////////////////////////////////////////////////////////////

GeometryObject::GeometryObject()
: m_useColors(true)
, m_useNormals(true)
, m_useTexCoords(true)
{
	m_primitive = Render::Primitive::Triangles;
}

void GeometryObject::toVertexArray(VertexArray& varray) const
{
	VertexFormat::Attribute position_attribute;
	VertexFormat::Attribute color_attribute;

	position_attribute.hint = VertexFormat::Position;
	color_attribute.hint    = VertexFormat::Color;

	position_attribute.numComponents = 3;
	position_attribute.size = sizeof(float);

	color_attribute.numComponents = 4;
	color_attribute.size = sizeof(float);

	varray.format.attributes.push_back(position_attribute);
	varray.format.attributes.push_back(color_attribute   );

	// Two channels of data need to be copied now
	varray.allocateData(vertices.size());

	struct vertex_format_struct
	{
		vec3 p;
		vec4 c;
	};

	vertex_format_struct* vertex_data = reinterpret_cast<vertex_format_struct*>(&varray._data[0]);

	for(std::size_t i = 0; i < vertices.size(); ++i)
	{
		vertex_data[i].p = vertices[i];
		vertex_data[i].c.x = (float)colors[i].r / 255.f;
		vertex_data[i].c.y = (float)colors[i].g / 255.f;
		vertex_data[i].c.z = (float)colors[i].b / 255.f;
		vertex_data[i].c.w = (float)colors[i].a / 255.f;
	}
}


void GeometryObject::onDraw(GraphicsDevice* renderer)
{
	if (vertices.size() == 0)
		return;

	renderer->enableVertexAttribArray(0);
	if(m_useColors && colors.size() > 0) renderer->enableVertexAttribArray(1);
	if(m_useTexCoords && texcoords0.size() > 0) renderer->enableVertexAttribArray(2);
	if(m_useNormals && normals.size() > 0) renderer->enableVertexAttribArray(3);
	if(boneIDs.size() > 0) renderer->enableVertexAttribArray(4);
	if(boneWeights.size() > 0) renderer->enableVertexAttribArray(5);

	renderer->setVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &vertices[0]);
	if(m_useColors && colors.size() > 0)       renderer->setVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0, &colors[0]);
	if(m_useTexCoords && texcoords0.size() > 0) renderer->setVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &texcoords0[0]);
	if(m_useNormals && normals.size() > 0)     renderer->setVertexAttribPointer(3, 3, GL_FLOAT, false, 0, &normals[0]);
	if(boneIDs.size() > 0)     renderer->setVertexAttribPointer(4, 4, GL_FLOAT, false, 0, &boneIDs[0]);
	if(boneWeights.size() > 0)     renderer->setVertexAttribPointer(5, 4, GL_FLOAT, false, 0, &boneWeights[0]);
	   
	renderer->drawArrays(m_primitive, 0, vertices.size());

	renderer->disableVertexAttribArray(0);
	if(m_useColors && colors.size() > 0) renderer->disableVertexAttribArray(1);
	if(m_useTexCoords && texcoords0.size() > 0) renderer->disableVertexAttribArray(2);
	if(m_useNormals && normals.size() > 0) renderer->disableVertexAttribArray(3);
	if(boneIDs.size() > 0) renderer->disableVertexAttribArray(4);
	if(boneWeights.size() > 0) renderer->disableVertexAttribArray(5);
}


/// Save the geometry to a file in a raw format
bool GeometryObject::saveToFile(const String& filename)
{
	File fp(filename, IODevice::BinaryWrite);
	if(fp)
	{
		DataStream writer(fp);

		// write vertices
		writer << static_cast<Int64>(vertices.size());
		if(vertices.size() > 0) fp.write(reinterpret_cast<char*>(&vertices[0]), vertices.size() * sizeof(vec3));

		// write normals
		writer << static_cast<Int64>(normals.size());
		if(normals.size() > 0) fp.write(reinterpret_cast<char*>(&normals[0]), normals.size() * sizeof(vec3));

		// write texcoords
		writer << static_cast<Int64>(texcoords0.size());
		if(texcoords0.size() > 0) fp.write(reinterpret_cast<char*>(&texcoords0[0]), texcoords0.size() * sizeof(vec2));

		// write colors
		writer << static_cast<Int64>(colors.size());
		if(colors.size() > 0) fp.write(reinterpret_cast<char*>(&colors[0]), colors.size() * sizeof(Color));
	}

	return true;
}

/// Load the geometry from a raw format file
bool GeometryObject::loadFromFile(const String& filename)
{
	File fp(filename, IODevice::BinaryRead);
	if(fp)
	{
		DataStream reader(fp);

		// read vertices
		Int64 vertexCount;
		reader >> vertexCount;
		vertices.resize(vertexCount);
		if(vertexCount > 0) fp.read(reinterpret_cast<char*>(&vertices[0]), sizeof(vec3) * vertexCount);

		// read normals
		Int64 normalCount;
		reader >> normalCount;
		normals.resize(normalCount);
		if(normalCount> 0) fp.read(reinterpret_cast<char*>(&normals[0]), sizeof(vec3) * normalCount);

		// read texcoords
		Int64 texCoordCount;
		reader >> texCoordCount;
		texcoords0.resize(texCoordCount);
		if(texCoordCount> 0) fp.read(reinterpret_cast<char*>(&texcoords0[0]), sizeof(vec2) * texCoordCount);

		// read colors
		Int64 colorCount;
		reader >> colorCount;
		colors.resize(colorCount);
		if(colorCount> 0) fp.read(reinterpret_cast<char*>(&colors[0]), sizeof(Color) * colorCount);

		Log("GeometryData::loadFromFile(%s): Loaded %d vertices", filename.c_str(), vertexCount);
	
	}
	else 
		return false;

	return true;
}

void GeometryObject::addBox(float width, float height, float depth)
{
	float hx = width / 2.f;
	float hy = height / 2.f;
	float hz = depth / 2.f;

	float verticesr[] = {
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

	vertices.resize(6 * 6);
	memcpy(&vertices[0], verticesr, sizeof(float) * 6 * 6 * 3);

	texcoords0.resize(6*6);
	memcpy(&texcoords0[0], texcoords, sizeof(float) * 6 * 6 * 2);	
}

/// Silly plane adding, to be refactored
void GeometryObject::addPlane(float width, float depth, float height)
{
	float hx = width / 2.f;
	float hz = depth / 2.f;

	float verticesraw[] = {
		-hx,height,-hz ,  -hx,height,hz , hx, height, hz   ,  hx,height,-hz  ,-hx, height, -hz  , hx,height,hz //top
	};

	float texcoords[] = 
	{
		0.f,0.f ,  0.f,1.f , 1.f,1.f  , 1.f,0.f , 0.f, 0.f  , 1.f,1.f //top
	};

	vertices.resize(6);
	memcpy(&vertices[0], verticesraw, sizeof(float)* 6 * 3);

	texcoords0.resize(6);
	memcpy(&texcoords0[0], texcoords, sizeof(float) * 6 * 2);
}

void GeometryObject::randomFaceColors()
{
	colors.resize(vertices.size());
	for(std::size_t i = 0; i < vertices.size(); i += 6)
	{
		Color c(math::randomInt(0,255), math::randomInt(0,255), math::randomInt(0,255));
		colors[i] = c;
		colors[i+1] = c;
		colors[i+2] = c;
		if(i+3 < vertices.size())
		{
			colors[i+3] = c;
			colors[i+4] = c;
			colors[i+5] = c;
		}
		
	}
}

void GeometryObject::setAllColors(Color color)
{
	colors.resize(vertices.size());
	for(std::size_t i = 0; i < colors.size(); ++i)
	{
		colors[i] = color;
	}
}

void GeometryObject::scaleUV(float factor)
{
	for(std::size_t i = 0; i < texcoords0.size(); ++i)
	{
		texcoords0[i].x *= factor;
		texcoords0[i].y *= factor;
	}
}

void GeometryObject::offsetUV(float u, float v)
{
	for(std::size_t i = 0; i < texcoords0.size(); ++i)
	{
		texcoords0[i].x += u;
		texcoords0[i].y += v;
	}
}




/// Generates normals for the geometry
void GeometryObject::generateNormals()
{
	normals.resize(vertices.size());
	for(int i = 0; i < vertices.size(); i+=3)
	{
		// triangle is m_vertices[i] .. i+1 i+2
		Vec3f normal(0,0,0);

		Vec3f edge1 = vertices[i+1] - vertices[i];
		Vec3f edge2 = vertices[i+2] - vertices[i];
		normal = edge1.cross(edge2);
		normal.normalize();

		normals[i] = normal;
		normals[i+1] = normal;
		normals[i+2] = normal;
	}
}


void GeometryObject::addCylinder()
{
	float r = 1;
	float h = 5;

	int hg_segments = 5;
	int rd_segments = 100;
	float rd_increment = math::pi*2 / rd_segments;

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

			vertices.push_back(p1);
			vertices.push_back(p2);
			vertices.push_back(p3);

			vertices.push_back(p3);
			vertices.push_back(p2);
			vertices.push_back(p4);
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
void GeometryObject::addTorusKnot(int p, int q)
{
	int segments = 1500;
	for(float theta = 0.f + math::pi*2 / segments; theta < math::pi*2; theta += math::pi*2 / segments)
	{
		float r = cos(q * theta) + 2;
		Vec3f point(r * cos(p * theta), r * sin(p * theta), -sin(q * theta));
		vertices.push_back(point);
	}
}

/// Generates the geometry of a torus knot
void GeometryObject::addTorus(int p, int q)
{
	
	float extrusionWidth = 2.f;
	int i_segments = 40;
	for(int i = 0; i < i_segments; ++i)
	{
		float theta = i * math::pi*2 / i_segments;
		float ptheta = theta - math::pi*2 / i_segments;

		int k_segments = 4;
		for(int k = 0; k < k_segments; ++k)
		{
			float theta2 = k * math::pi*2 / k_segments;
			float ptheta2 = theta2 - math::pi*2 / k_segments;

			// The 4 points of the quad
			Vec3f p1, p2, p3, p4;
			p1 = Vec3f(cos(theta) * (p + cos(theta2)), sin(theta) * (p + cos(theta2)), sin(theta2));
			p2 = Vec3f(cos(ptheta) * (p + cos(theta2)), sin(ptheta) * (p + cos(theta2)), sin(theta2));
			p3 = Vec3f(cos(theta) * (p + cos(ptheta2)), sin(theta) * (p + cos(ptheta2)), sin(ptheta2));
			p4 = Vec3f(cos(ptheta) * (p + cos(ptheta2)), sin(ptheta) * (p + cos(ptheta2)), sin(ptheta2));

			
			vertices.push_back(p1);
			vertices.push_back(p2);
			vertices.push_back(p3);

			vertices.push_back(p3);
			vertices.push_back(p2);
			vertices.push_back(p4);
		}
	}

	generateNormals();
	setAllColors(Color::White);
}

/// Make sure there is a uv set
void GeometryObject::ensureUV0()
{
	if (texcoords0.size() == 0)
	{
		texcoords0.resize(vertices.size());
		for (auto& uv : texcoords0)
		{
			uv.x = uv.y = 0.f;
		}
	}
}

/// Apply an arbitrary transform to this mesh
void GeometryObject::applyTransform(mat4 transf)
{
	for (auto& v : vertices)
	{
		v = transf * v;
	}
}

/// Scales the mesh by a factor
void GeometryObject::scale(float xfactor, float yfactor, float zfactor)
{
	for (auto& v : vertices)
	{
		v.x *= xfactor;
		v.y *= yfactor;
		v.z *= zfactor;
	}
}

/// Operator overload for adding torus knots
GeometryObject& GeometryObject::operator<<(const TorusKnotDef& torus)
{
	addTorusKnot(torus.p, torus.q);
	return *this;
}

/// Operator overload for adding torus knots
GeometryObject& GeometryObject::operator<<(const TorusDef& torus)
{
	addTorus(torus.p, torus.q);
	return *this;
}

Vec3f calculateNormal(Vec3f p1, Vec3f p2, Vec3f p3)
{
	return Vec3f();
}


NEPHILIM_NS_END