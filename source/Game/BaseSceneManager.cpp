#include <Nephilim/Game/BaseSceneManager.h>

NEPHILIM_NS_BEGIN

/// Create a new scene with a string name
rzr::Scene* BaseSceneManager::createScene(const String& name)
{
	Scene* scene = new Scene();

	mScenes.push_back(scene);

	return scene;
}

NEPHILIM_NS_END