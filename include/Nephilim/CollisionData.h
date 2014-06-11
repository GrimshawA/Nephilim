#ifndef NephilimCollisionData_h__
#define NephilimCollisionData_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Strings.h>

#include <vector>
#include <list>

NEPHILIM_NS_BEGIN

/**
	\class CollisionData
	\brief Storage for collision information of a world

	This class stores collision information to generate the data for the physics systems.
	Ideally, this class stores a subset or the whole collision information of an entire
	game level. For example, for a sophisticated platformer game, this class is able to
	hold and serialize all the collision data necessary for the game to be playable.

	Contains N bodies, and each body contains N shapes that are under the influence of the body.
	For example, a single body can contain all the collision information of an entire level static data,
	or each individual tile or line segment can also belong to its own body. The best practice depends on
	the game being worked on.

	Examples of supported shapes are:
	- Sphere
	- Circle
	- Rect
	- Box
	- Triangle Mesh
	- Convex Polygon
	- Line segments
	- ...
*/
class NEPHILIM_API CollisionData
{
public:

	String s;

	class Shape
	{
	public:
		enum Type
		{

		};

		vec2 position;
		vec2 size;
	};

	class Body
	{
	public:
		std::list<Shape> mShapes;

		void addRect(float center_x, float center_y, float width, float height);
	};

	/// Add a new body to the collection
	Body& addBody();

	std::list<Body> mBodies;
	typedef std::list<Body>::iterator BodyIterator;
	typedef std::list<Shape>::iterator ShapeIterator;
};

NEPHILIM_NS_END
#endif // NephilimCollisionData_h__
