#ifndef NephilimGeometry_h__
#define NephilimGeometry_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Math/Vectors.h>

#include <Nephilim/Graphics/Drawable.h>
#include <Nephilim/Math/Matrix.h>
#include <Nephilim/Foundation/Color.h>
#include <Nephilim/Graphics/RenderModes.h>
#include "Strings.h"

#include <vector>
#include <stdint.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;

struct TorusKnotDef
{
	TorusKnotDef(int p, int q)
	{
		this->p = p;
		this->q = q;
	}

	int p, q;
};

struct TorusDef
{
	TorusDef(int p, int q)
	{
		this->p = p;
		this->q = q;
	}

	int p, q;
};

/**
	\class Geometry
	\brief Utility class to generate geometry, procedurally manipulate it and render it
*/
class NEPHILIM_API Geometry
{
public:

	/// Generate a plane with center in origin, facing its normal direction, with given dimensions
	static Geometry GeneratePlane(Vector3D origin, Vector3D normal, Vector2D dimensions);

	/// Generate a sky box mesh
	static Geometry GenerateSkyBox();


	/// Triangle
	struct Face
	{
		uint16_t v1;
		uint16_t v2;
		uint16_t v3;
	};

	/// Triangle list
	std::vector<Face>     _faces;
	std::vector<Vector3D> _positions;
	std::vector<vec4>     _colors;
	std::vector<vec2>     _texcoord;
};


/**
	\ingroup Graphics
	\class GeometryData
	\brief Holds raw geometry data for processing

	Right now only draws with shaders.
*/
class NEPHILIM_API GeometryData : public Drawable
{
public:
	GeometryData();

	Render::Primitive::Type m_primitive;

	/// Generates the geometry of a origin-centered box
	void addBox(float width, float height, float depth);

	/// Generates the geometry of a torus knot
	void addTorusKnot(int p, int q);
	void addTorus(int p, int q);
	void addCylinder();

	void randomFaceColors();

	/// Save the geometry to a file in a raw format
	bool saveToFile(const String& filename);

	/// Load the geometry from a raw format file
	bool loadFromFile(const String& filename);

	/// Silly plane adding, to be refactored
	void addPlane(float width, float depth, float height);

	void scaleUV(float factor);

	void offsetUV(float u, float v);

	/// Operator overload for adding torus knots
	GeometryData& operator<<(const TorusKnotDef& torus);
	GeometryData& operator<<(const TorusDef& torus);

	/// Generates normals for the geometry
	void generateNormals();

	void setAllColors(Color color);

	void toVertexArray(VertexArray& varray);

	virtual void onDraw(GraphicsDevice* renderer);

	std::vector<Vec3f> m_vertices;
	std::vector<Color> m_colors;
	std::vector<Vec3f> m_normals;
	std::vector<Vec2f> m_texCoords;
	std::vector<vec4> boneIDs;
	std::vector<vec4> boneWeights;

	bool m_useColors;
	bool m_useNormals;
	bool m_useTexCoords;
};

class NEPHILIM_API GeomObject
{
public:
	// A face is made of three indices into an array of vertices
	struct GeomFace
	{
		uint16_t v1;
		uint16_t v2;
		uint16_t v3;
	};

	std::vector<GeomFace> faces;
};


/// Calculates the normal of a triangle - TODO
Vec3f calculateNormal(Vec3f p1, Vec3f p2, Vec3f p3);

NEPHILIM_NS_END

#endif // NephilimGeometry_h__
