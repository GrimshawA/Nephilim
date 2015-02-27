#include <Nephilim/UI/UxWorldViewport.h>
#include <Nephilim/World/World.h>
#include <Nephilim/World/Systems/RenderSystem.h>

NEPHILIM_NS_BEGIN

UxWorldViewport::UxWorldViewport(World* worldPtr)
: _world(worldPtr)
{

}

void UxWorldViewport::render(GraphicsDevice* gdi)
{
	if (_world)
	{
		_world->_renderSystem->render();
	}
}

/// Get the object name of this node
const char* UxWorldViewport::getName()
{
	if (_world)
	{
		return _world->name.c_str();
	}
	else
	{
		return "null";
	}
}

/// Get the class name of this node
const char* UxWorldViewport::getClassName()
{
	return "UxWorldViewport";
}


NEPHILIM_NS_END