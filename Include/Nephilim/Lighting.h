#ifndef PARABOLA_LIGHTING_H
#define PARABOLA_LIGHTING_H

#include "Platform.h"
#include "Rect.h"
#include "SceneRenderer.h"
#include "Window.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API LightingEffects{
public:	
	LightingEffects();

	bool ready();

	void setView(View &view);

	void create(Rect &area, Window *window);

	void render(SceneRenderer* renderer);

private:
	bool myReady;
	class LightingHolder;
	LightingHolder *myData;
	FloatRect myBounds;
};

class NEPHILIM_API ShadowCaster{
public:

};

NEPHILIM_NS_END
#endif