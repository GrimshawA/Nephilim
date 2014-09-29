#include <Nephilim/UI/UIComponentDebug.h>

#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/StringList.h>
#include <Nephilim/RectangleShape.h>
#include <Nephilim/UI/UIView.h>
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
		if(value == "white")
		{
			mColor = Color::White;
		}
	}
}



void UIComponentDebugColor::onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform)
{
	RectangleShape backRect(view->getBounds(), mColor);
	renderer->draw(backRect);
}


NEPHILIM_NS_END