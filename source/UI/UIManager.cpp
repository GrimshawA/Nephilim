#include <Nephilim/UI/UIManager.h>
#include <Nephilim/UI/UICanvas.h>

NEPHILIM_NS_BEGIN

/// Create a new canvas, uniquely named
UICanvas* UIManager::createCanvas(const String& name)
{
	UICanvas* canvas = nullptr;

	for (auto c : canvasList)
	{
		if (c->m_name == name)
			canvas = c;
	}

	if (!canvas)
	{
		canvas = new UICanvas();
		canvas->m_name = name;
		canvasList.push_back(canvas);
	}
	
	return canvas;
}

NEPHILIM_NS_END