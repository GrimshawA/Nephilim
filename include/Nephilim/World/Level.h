#ifndef NephilimLevel_h__
#define NephilimLevel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Foundation/String.h>

#include <Nephilim/World/Actor.h>
#include <Nephilim/World/ASpriteComponent.h>

#include <vector>

NEPHILIM_NS_BEGIN

class World;
class Landscape;

/**
	\class Level
	\brief A level is a collection of scene objects to make up gameplay

	Levels can be really big or really small. Everything inside a level
	is relative to the level origin, and is moved together with this origin,
	if the level moves around.

	Each level also has 64 bit integer bounds, that allow to define levels over an
	insanely large world.

	Levels are loaded into World objects and stay loaded in there until a streamer
	decides to unload them, or user code.

	There is a maximum size for each level, which defined by a constant. This is needed
	to ensure all things positioned inside this level with floating point coordinates,
	stay with valid numbers.

	Levels are usually cells in a bigger grid in the World object, in case of open world games.
	By putting things well inside their own levels, the coordinate systems stay robust, content
	can be loaded and unload on the fly with ease, etc.

	Levels are a collection of static and dynamic assets, each in their own
	organization, for maximizing performance. For example, if there are many objects with shared
	render settings, they can be batched together to gain speed. If every prop laid in the map
	is set as dynamic, and nothing is actually moving it around or changing anything about, then
	a potential optimization was wasted.

	A nice thing about levels is that maps made completely independently will be able to come together in the same world, and loaded/unloaded
	at will. Its ideal that they are designed to fit seamlessly, but this is not required.

	Levels are collections of:
	1) Static sprites and meshes, which never ever change
	2) Landscape objects with terrains, tilemaps, voxels or other.
	3) Actor spawn locations, with Actor class and initial data

	Levels should not be used on their own, but through World objects.
*/
class NEPHILIM_API Level
{
public:
	/// The dimensions of the level, this computes the absolute bounding box
	float width, height, depth;

	/// The unique name of this level
	String name;

	/// World that has this level loaded
	World* world;

	/// Landscape array of this level
	std::vector<Landscape*> landscapes;

public: // TEMP STUFF; FOR PROTOTYPING World MODULE

	std::vector<ASpriteComponent> sprites;

public:
	/// Default construction of a level object
	Level();

};

NEPHILIM_NS_END
#endif // NephilimLevel_h__
