#include "Nephilim/EventHandler.h"

NEPHILIM_NS_BEGIN

	void EventHandler::OnMouseButtonDown(unsigned int MouseButton, int x, int y, int keyMod){}

	void EventHandler::OnMouseButtonUp(unsigned int MouseButton, int x, int y, int keyMod){}

	void EventHandler::OnMouseMove(int x, int y, int keyMod){}

	void EventHandler::OnMouseWheel(int delta, int keyMod){}

	void EventHandler::OnKeyPress(unsigned int Key, int keyMod){}

	void EventHandler::OnTextEntered(unsigned int Key){}

	void EventHandler::OnKeyReleased(unsigned int Key, int keyMod){}

NEPHILIM_NS_END