#ifndef NephilimProceduralGeometry_h__
#define NephilimProceduralGeometry_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/VertexArray.h>
#include <Nephilim/Foundation/Vector.h>

#include <Nephilim/Graphics/Drawable.h>
#include <Nephilim/Foundation/Matrix.h>
#include <Nephilim/Foundation/Color.h>
#include <Nephilim/Graphics/RenderModes.h>
#include <Nephilim/Foundation/String.h>

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
	\brief Procedural utilities for creating geometry

	This class pairs up with GeometryObject, as multiple can be put together
	to form more complex geometries.

	Each GeometryObject is a single mesh, with a single set of faces and vertices,
	etc.

	This kit is a convenient geometry manipulator, for quick prototyping and other uses.
	It is compatible with the engine's VertexBuffer and VertexArray, as well as the geometry
	file formats, so we can actually use this class as a part of the production pipeline.

	Be careful as Geometry isn't necessarily fast, especially if you try to render it directly
	without first uploading to an appropriate StaticMesh, SkeletalMesh or other.

	Any kind of procedural generation code is encouraged to use GeometryObject as a means
	to compose the data, and then upload it to the World module.
*/
class NEPHILIM_API Geometry
{
public:

	/// Generate a plane with center in origin, facing its normal direction, with given dimensions
	static Geometry GeneratePlane(Vector3D origin, Vector3D normal, Vector2D dimensions);

	/// Generate a sky box mesh
	static Geometry GenerateSkyBox();
};


/**
	\class GeometryObject
	\brief Holds to a single geometric mesh

	A single mesh is a very well defined set of positions, the indices that compose its faces
	and additional per vertex attributes for other things.

	This class can be rendered for debug purposes, but it is meant for occasional
	geometry manipulation, which can then be uploaded directly into more appropriate 
	engine facilities, who will draw things with full efficiency.
*/
class NEPHILIM_API GeometryObject : public Drawable
{
public:
	
	

	/// The array of positions in the mesh
	std::vector<Vector3D> vertices;

	/// Each vertex can have an associated color
	std::vector<Color> colors;

	/// Normals for each vertex for lighting
	std::vector<Vector3D> normals;

	/// First channel of texture coordinates
	std::vector<Vector2D> texcoords0;

	/// Each vertex can have a bone influences list
	std::vector<Vector4D> boneIDs;

	/// Each vertex can have a bone influences list
	std::vector<Vector4D> boneWeights;

	/// Faces (triangles) of the mesh
	std::vector<Vec3<uint16_t> > faces;

	bool m_useColors;
	bool m_useNormals;
	bool m_useTexCoords;

	Render::Primitive::Type m_primitive;

public:


	GeometryObject();

	/// Scales the mesh by a factor
	void scale(float xfactor, float yfactor, float zfactor);

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
	GeometryObject& operator<<(const TorusKnotDef& torus);
	GeometryObject& operator<<(const TorusDef& torus);

	/// Generates normals for the geometry
	void generateNormals();

	void setAllColors(Color color);

	/// Copies our mesh into a vertex array with proper structure
	void toVertexArray(VertexArray& varray) const;

	virtual void onDraw(GraphicsDevice* renderer);

public:

	/// Merges two meshes into one appropriately
	static GeometryObject Merge(const GeometryObject& A, const GeometryObject& B);
};

/// Calculates the normal of a triangle - TODO
Vec3f calculateNormal(Vec3f p1, Vec3f p2, Vec3f p3);

NEPHILIM_NS_END

#endif // NephilimProceduralGeometry_h__
