#include <Nephilim/UI/UIPainter.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/RectangleShape.h>
#include <Nephilim/Graphics/Text.h>

NEPHILIM_NS_BEGIN

namespace
{
	int closestInteger(float v)
	{
		return static_cast<int>(v + 0.5f);
	}
};

/// Draw a rectangle
void UIPainter::drawRect(FloatRect rectangle)
{
	RectangleShape rectShape(rectangle, currentColor);
	rectShape.useOwnTransform = false;
	graphicsDevice->setModelMatrix(baseMatrix * rectShape.getTransform().getMatrix());
	graphicsDevice->draw(rectShape);
}

/// Renders the text at the default position
void UIPainter::drawText(const String& text)
{
	if (activeFont)
	{
		Text textObject;
		textObject.setCharacterSize(currentTextSize);
		textObject.setString(text);
		textObject.setColor(currentTextFill);
		textObject.setOrigin(0.f, 0.f);
		textObject.setFont(*activeFont);

		graphicsDevice->setModelMatrix(baseMatrix * textObject.getTransform().getMatrix());
		textObject.useOwnTransform = false;
		graphicsDevice->draw(textObject);
	}
}

/// Renders the text at the current origin
void UIPainter::drawText(Vector2D point, const String& text)
{
	if (activeFont)
	{
		Text textObject;
		textObject.setCharacterSize(currentTextSize);
		textObject.setString(text);
		textObject.setColor(currentTextFill);
		textObject.setOrigin(0.f, 0.f);
		textObject.setFont(*activeFont);
		textObject.setPosition(point);

		graphicsDevice->setModelMatrix(baseMatrix * textObject.getTransform().getMatrix());
		textObject.useOwnTransform = false;
		graphicsDevice->draw(textObject);
	}
}

/// Renders the text at the current origin
void UIPainter::drawText(FloatRect rectangle, int flags, const String& text)
{
	if (activeFont)
	{
		Text textObject;
		textObject.setCharacterSize(currentTextSize);
		textObject.setString(text);
		textObject.setColor(currentTextFill);
		textObject.setOrigin(0.f, 0.f);
		textObject.setFont(*activeFont);

		if ((flags & PainterFlags::AlignCenterH) == PainterFlags::AlignCenterH)
		{
			textObject.setOrigin(closestInteger(textObject.getLocalBounds().width / 2.f), closestInteger(textObject.getOrigin().y));
			textObject.setPosition(closestInteger(rectangle.left + rectangle.width / 2.f), closestInteger(textObject.getPosition().y));
		}
		if ((flags & PainterFlags::AlignCenterV) == PainterFlags::AlignCenterV)
		{
			textObject.setOrigin(closestInteger(textObject.getOrigin().x), closestInteger(textObject.getLocalBounds().height / 2.f));
			textObject.setPosition(closestInteger(textObject.getPosition().x), closestInteger(rectangle.top + rectangle.height / 2.f));
		}
		

		graphicsDevice->setModelMatrix(baseMatrix * textObject.getTransform().getMatrix());
		textObject.useOwnTransform = false;
		graphicsDevice->draw(textObject);
	}
}

/// Set a new fill color for subsequent shapes
void UIPainter::setFillColor(Color fill)
{
	currentColor = fill;
}

/// Set a new fill color for subsequent text drawing
void UIPainter::setTextFillColor(Color textFill)
{
	currentTextFill = textFill;
}

NEPHILIM_NS_END