#include <Nephilim/UI/UIComponentListView.h>
#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/UI/UIComponentTouchScroll.h>
#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIComponentText.h>

#include <Nephilim/Text.h>

NEPHILIM_NS_BEGIN

void UIComponentListView::onAttach(UIView* view)
{
	// Lets attach 10 sample children to try it out
	for(int i = 0; i < 50; i++)
	{
		UIView* entityChild = new UIView();
		entityChild->setRect(view->getPosition().x, view->getPosition().y + i * 25.f, view->getSize().x, 25.f);
		entityChild->addComponent(new UIComponentDebugColor(Color::Black));
		entityChild->addComponent(new UIComponentText("Entity" + String::number(i+1), UIComponentText::Center, UIComponentText::Center));
		view->attach(entityChild);
	}

	view->m_clipChildren = true;
}

void UIComponentListView::onRender(Renderer* renderer, UIView* view)
{
	RectangleShape backgroundRect;
	backgroundRect.setColor(Color(240,240,240,40));
	backgroundRect.setRect(view->getBounds());
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