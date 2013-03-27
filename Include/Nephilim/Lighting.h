#ifndef PARABOLA_LIGHTING_H
#define PARABOLA_LIGHTING_H

#include "Platform.h"
#include "Rect.h"
#include "SceneRenderer.h"
#include "Window.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API LightingEffects{
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

class PARABOLA_API ShadowCaster{
public:

};

PARABOLA_NAMESPACE_END
#endif