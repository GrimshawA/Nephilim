#ifndef Geometry_h__
#define Geometry_h__

#include "Platform.h"
#include "Vectors.h"
#include "Drawable.h"
#include "Matrix.h"
#include "Color.h"
#include "RenderModes.h"
#include "Strings.h"

#include <vector>

NEPHILIM_NS_BEGIN

class Renderer;

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

	/// Operator overload for adding torus knots
	GeometryData& operator<<(const TorusKnotDef& torus);
	GeometryData& operator<<(const TorusDef& torus);

	/// Generates normals for the geometry
	void generateNormals();

	void setAllColors(Color color);

	virtual void onDraw(Renderer* renderer);

	std::vector<Vec3f> m_vertices;
	std::vector<Color> m_colors;
	std::vector<Vec3f> m_normals;
	std::vector<Vec2f> m_texCoords;

	bool m_useColors;
	bool m_useNormals;
	bool m_useTexCoords;
};


/// Calculates the normal of a triangle - TODO
Vec3f calculateNormal(Vec3f p1, Vec3f p2, Vec3f p3);

NEPHILIM_NS_END

#endif // Geometry_h__
