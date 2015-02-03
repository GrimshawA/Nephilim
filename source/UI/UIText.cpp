#include <Nephilim/UI/UIText.h>
#include <Nephilim/Foundation/Math.h>

NEPHILIM_NS_BEGIN

/// Set the contents of this UIText
void UIText::setContent(const String& content)
{	
	text_string = content;
	dirty = true;
}

void UIText::updateContent()
{
	buttonLabel.setFont(*getCore()->m_defaultFont);
	buttonLabel.setString(text_string);
	buttonLabel.setCharacterSize(12);
	buttonLabel.setColor(Color::Black);

	setSize(buttonLabel.getLocalBounds().width, buttonLabel.getLocalBounds().height);

	dirty = false;
}


/// Draw the text node
void UIText::onDraw(GraphicsDevice* graphicsDevice, const mat4& viewToWorld)
{	
	if (dirty)
	{
		updateContent();
	}

	//graphicsDevice->setModelMatrix(viewToWorld);
	graphicsDevice->draw(buttonLabel);
}

NEPHILIM_NS_END