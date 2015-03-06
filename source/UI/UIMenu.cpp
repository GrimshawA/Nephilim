#include <Nephilim/UI/UIMenu.h>

//#include <Nephilim/UI/UIComponentDebug.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

UIMenu::UIMenu()
{

}

void UIMenu::onAttach(UIView* view)
{
	view->onClick.connect(sigc::mem_fun(this, &UIMenu::toggleMenu));
}

void UIMenu::toggleMenu()
{
/*	UICore* core = mParent->getCore();
	if (core && core->menuElementStack.empty())
	{
		Log("OPENING MENU");

		UIView* menuView = new UIView();
		menuView->setRect(mParent->getWorldPosition().x, mParent->getWorldPosition().y + mParent->height(), 100.f, 100.f);
		menuView->addController(new UIComponentDebugColor(Color(17, 17, 17)));
		core->menuElementStack.push_back(menuView);
	}
	else
	{
		Log("Closing menu");

		core->menuElementStack.clear();
	}*/
}


void UIMenu::onEvent(Event event, UIView* view)
{

}

void UIMenu::onRender(GraphicsDevice* renderer, UIView* view)
{

}

NEPHILIM_NS_END