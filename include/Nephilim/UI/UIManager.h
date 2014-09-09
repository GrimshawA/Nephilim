#ifndef UIManager_h__
#define UIManager_h__

#include <Nephilim/Platform.h>
#include "Strings.h"
#include "Rect.h"

#include <map>

NEPHILIM_NS_BEGIN
class Renderer;
class UIDocument;

class NEPHILIM_API UIManager
{
public:
	UIDocument* create(const String &name);

	void draw(const String& name, Renderer* renderer);

	void setArea(float x, float y, float w, float h);

	std::map<String, UIDocument*> m_windows;
	FloatRect area;
};

NEPHILIM_NS_END
#endif // UIManager_h__
