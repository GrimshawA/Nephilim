#ifndef UIManager_h__
#define UIManager_h__

#include "Platform.h"
#include "Strings.h"
#include "Rect.h"

#include <map>

PARABOLA_NAMESPACE_BEGIN
class Renderer;
class UIWindow;

class PARABOLA_API UIManager
{
public:
	UIWindow* create(const String &name);

	void draw(const String& name, Renderer* renderer);

	void setArea(float x, float y, float w, float h);

	std::map<String, UIWindow*> m_windows;
	FloatRect area;
};

PARABOLA_NAMESPACE_END
#endif // UIManager_h__
