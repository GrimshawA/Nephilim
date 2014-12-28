#ifndef NephilimGameBaseSceneManager_h__
#define NephilimGameBaseSceneManager_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Time.h>
#include <Nephilim/World/World.h>


NEPHILIM_NS_BEGIN

/**
	\class BaseSceneManager
	\brief Plugs into the BaseGame to support multiple scenes in the same game

	BaseGame is the game ready solution in the engine, providing lots of features
	by default in order for the task of making a game really easy.

	After careful analysis, it was concluded that many games require multiple scenes to function,
	as in, multiple different spaces to operate in. For example,
	many games feature the game world with all the entities, and when its paused,
	we can see another alive game world in the background, while the main one also stays in memory.

	This is what the scene manager is for. On a big array of cases
	only one scene will be instanced and ever needed, but since this rule
	is broken all the time, the engine supports natively to handle multiple scenes.

	There are a lot of use cases for this. Another good example is when we make a game inside a game,
	like when we travel in our 3D world but are allowed to go into a TV set and play a smaller game on it.
	Here, our 3D world would be the main scene, but a second scene would be used for the small game entities and
	logic. Then, the secondary scene would be rendered to a texture and displayed in a material in the main world.

	This is entirely possible and supported.
*/
class NEPHILIM_API BaseSceneManager
{
public:

	std::vector<World*> mScenes;

public:

	/// Create a new scene with a string name
	World* createScene(const String& name);

	/// Get a scene by its name
	World* getScene(const String& name);
};

NEPHILIM_NS_END
#endif // NephilimGameBaseSceneManager_h__
