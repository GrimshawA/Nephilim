#ifndef Jumpy_h__
#define Jumpy_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Shader.h>
#include <Nephilim/ShaderGen.h>
#include <Nephilim/Package.h>
#include <Nephilim/Framebuffer.h>
using namespace nx;

#include "GameState.hpp"

class Jumpy : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);
	void nextState();
	void lastState();

	bool m_running;
	std::stack<GameState*> states;
};
#endif // Jumpy_h__
