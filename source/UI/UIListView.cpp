#include <Nephilim/UI/UIListView.h>
#include <Nephilim/Graphics/Text.h>

NEPHILIM_NS_BEGIN

void UIListView::onRender(GraphicsDevice* renderer, Widget* view)
{
	RectangleShape backgroundRect;
	backgroundRect.setColor(Color(240,240,240,40));
	backgroundRect.setRect(view->getRect());
	renderer->draw(backgroundRect);

	float itemHeight = view->getSize().y / 10.f;
	/*
	for(int i = 0; i < 10; i++)
	{
		RectangleShape backgroundRect2;
		backgroundRect2.setColor(Color(20,20,20,100));
		backgroundRect2.setSize(view->getSize().x, itemHeight);
		backgroundRect2.setPosition(view->getPosition().x, view->getPosition().y + itemHeight * i);
		backgroundRect2.setOutlineThickness(1.f);
		backgroundRect2.setOutlineColor(Color::White);
		renderer->draw(backgroundRect2);

		Text text;
		text.setCharacterSize(14);
		text.setString("Entity " + String::number(i+1));
		text.setColor(Color::White);
		text.setPosition(view->getPosition().x + view->getSize().x / 2.f, view->getPosition().y + itemHeight * i);
		text.setFont(*view->getContext()->m_defaultFont);
		text.setOrigin(text.getLocalBounds().width / 2.f, 0.f);
		renderer->draw(text);
	}*/
}

NEPHILIM_NS_END