#include <Nephilim/UI/UIDebugWidget.h>

#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Foundation/StringList.h>
#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Foundation/Math.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

UIDebugWidget::UIDebugWidget()
: mColor(Color::White)
{

}

UIDebugWidget::UIDebugWidget(const Color& color)
: mColor(color)
{

}

void UIDebugWidget::onAttach(UIView* view)
{
	
}

void UIDebugWidget::onPropertySet(const StringList& targetObject, const String& value)
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



void UIDebugWidget::onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform)
{
	renderer->setModelMatrix(parentTransform);
	RectangleShape backRect(FloatRect(0.f, 0.f, view->size.x, view->size.y), mColor);
	backRect.useOwnTransform = false;
	renderer->draw(backRect);
}


NEPHILIM_NS_END