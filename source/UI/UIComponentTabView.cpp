#include <Nephilim/UI/UIComponentTabView.h>
#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UI/UIComponentTouchScroll.h>
#include <Nephilim/UI/UIComponentText.h>
#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN
UIComponentTabView::UIComponentTabView()
{

}

void UIComponentTabView::onAttach(UIView* view)
{
	parent = view;
}

void UIComponentTabView::refreshTabButtons()
{
	// Add a button per tab
	for(std::size_t i = 0; i < tabs.size(); ++i)
	{
		UIView* tabButton = new UIView();
		tabButton->setRect(parent->getPosition().x + 50.f * i, parent->getPosition().y, 49.f, 20.f);
		tabButton->addComponent(new UIComponentDebugColor(Color::Grey));
		tabButton->addComponent(new UIComponentText("Tab " + String::number(i), UIComponentText::Center, UIComponentText::Center));
		tabButton->onClick.connect(sigc::bind(sigc::mem_fun(this, &UIComponentTabView::onTabButtonClicked), i));
		parent->attach(tabButton);
	}
}

/// Show another tab by its index
void UIComponentTabView::onTabButtonClicked(std::size_t index)
{
	if(index < 0 || index >= tabs.size() || tabs.size() == 0)
		return;

	for(std::size_t i = 0; i < tabs.size(); ++i)
	{
		tabs[i]->hide();
	}

	tabs[index]->show();
	tabs[index]->setRect(FloatRect(parent->getPosition().x, parent->getPosition().y + 20, parent->getSize().x, parent->getSize().y - 20.f));
}

void UIComponentTabView::onEvent(Event event, UIView* view)
{
	if(event.type == Event::KeyPressed)
	{
	/*	if(event.key.code == Keyboard::Num1)
		{
			// Activate first tab
			for(std::size_t i = 0; i < tabs.size(); ++i)
			{
				tabs[i]->hide();
			}

			tabs[0]->show();
			tabs[0]->setRect(FloatRect(view->getPosition().x, view->getPosition().y + 20, view->getSize().x, view->getSize().y - 20.f));
		}
		if(event.key.code == Keyboard::Num2)
		{
			// Activate first tab
			for(std::size_t i = 0; i < tabs.size(); ++i)
			{
				tabs[i]->hide();
			}

			tabs[1]->show();
			tabs[1]->setRect(FloatRect(view->getPosition().x, view->getPosition().y + 20, view->getSize().x, view->getSize().y - 20.f));
		}*/
	}
}

void UIComponentTabView::onRender(Renderer* renderer, UIView* view)
{
	RectangleShape topRect(FloatRect(view->getPosition().x, view->getPosition().y, view->getSize().x, 20.f), Color::White);
	renderer->draw(topRect);

	RectangleShape bottomRect(FloatRect(view->getPosition().x, view->getPosition().y + 20, view->getSize().x, view->getSize().y - 20.f), Color::Orange);
	renderer->draw(bottomRect);
}

NEPHILIM_NS_END