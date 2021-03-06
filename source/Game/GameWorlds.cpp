#include <Nephilim/Game/GameWorlds.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

/// Create a new scene with a string name
World* GameWorlds::createScene(const String& name)
{
	World* scene = new World();
	scene->name = name;
	mScenes.push_back(scene);
	return scene;
}

World* GameWorlds::getScene(const String& name)
{
	//Log("world %d", mScenes.size());

	for (size_t i = 0; i < mScenes.size(); ++i)
	{
		//Log("%s == %s", name.c_str(), mScenes[i]->name.c_str());
		if (mScenes[i]->name == name)
		{
			return mScenes[i];
		}
	}
	return nullptr;
}

NEPHILIM_NS_END