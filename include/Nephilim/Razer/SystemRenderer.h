#ifndef NephilimRazerSystemRenderer_h__
#define NephilimRazerSystemRenderer_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/System.h>
#include <Nephilim/Renderer.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

class Entity;

class NEPHILIM_API SystemRenderer : public System
{
public:
	SystemRenderer();

	virtual void render();
	
	void renderTilemap(Entity& entity);
	void renderMesh(Entity& entity);

	Renderer* mRenderer;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystemRenderer_h__
