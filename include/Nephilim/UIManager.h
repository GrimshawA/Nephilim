#ifndef UIManager_h__
#define UIManager_h__

#include "Platform.h"
#include "Strings.h"
#include "Rect.h"

#include <map>

NEPHILIM_NS_BEGIN
class Renderer;
class UIWindow;

class NEPHILIM_API UIManager
{
public:
	UIWindow* create(const String &name);

	void draw(const String& name, Renderer* renderer);

	void setArea(float x, float y, float w, float h);

	std::map<String, UIWindow*> m_windows;
	FloatRect area;
};

NEPHILIM_NS_END
#endif // UIManager_h__
