#include <Nephilim/Game/BaseGame.h>

NEPHILIM_NS_BEGIN

BaseGame::BaseGame()
{	
}

/// Create a new scene or return if already exists
rzr::Scene* BaseGame::createScene(const String& name)
{
	return sceneManager.createScene(name);
}


NEPHILIM_NS_END