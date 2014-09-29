#include <Nephilim/UI/UIManager.h>
#include <Nephilim/UI/UICanvas.h>

NEPHILIM_NS_BEGIN

/// Create a new canvas, uniquely named
UICanvas* UIManager::createCanvas(const String& name)
{
	UICanvas* canvas = new UICanvas();
	canvas->m_name = name;

	canvasList.push_back(canvas);

	return canvas;
}

NEPHILIM_NS_END