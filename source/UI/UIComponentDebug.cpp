#include <Nephilim/UI/UIComponentDebug.h>

#include <Nephilim/Renderer.h>
#include <Nephilim/StringList.h>
#include <Nephilim/RectangleShape.h>
#include <Nephilim/UIView.h>
#include <Nephilim/NxMath.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

UIComponentDebugColor::UIComponentDebugColor()
: mColor(Color::White)
{

}

UIComponentDebugColor::UIComponentDebugColor(const Color& color)
: mColor(color)
{

}

void UIComponentDebugColor::onAttach(UIView* view)
{
	
}

void UIComponentDebugColor::onPropertySet(const StringList& targetObject, const String& value)
{
	Log("UIComponentDebug(%s)", value.c_str());

	if(targetObject.size() == 2 && targetObject[0] == "debug" && targetObject[1] == "color")
	{
		if(value == "red")
		{
			mColor = Color::Red;
		}
		if(value == "blue")
		{
			mColor = Color::Blue;
		}
	}
}



void UIComponentDebugColor::onRender(Renderer* renderer, UIView* view)
{
	RectangleShape backRect(view->getBounds(), mColor);
	renderer->draw(backRect);
}


NEPHILIM_NS_END