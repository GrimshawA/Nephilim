#include <Nephilim/UI/UIComponentMenu.h>
#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

UIComponentMenuCaster::UIComponentMenuCaster()
{

}

void UIComponentMenuCaster::onAttach(UIView* view)
{
	view->onClick.connect(sigc::mem_fun(this, &UIComponentMenuCaster::toggleMenu));
}

void UIComponentMenuCaster::toggleMenu()
{
	UICore* core = mParent->getCore();
	if (core && core->menuElementStack.empty())
	{
		Log("OPENING MENU");

		UIView* menuView = new UIView();
		menuView->setRect(mParent->getWorldPosition().x, mParent->getWorldPosition().y + mParent->height(), 100.f, 100.f);
		menuView->addComponent(new UIComponentDebugColor(Color(17, 17, 17)));
		core->menuElementStack.push_back(menuView);
	}
	else
	{
		Log("Closing menu");

		core->menuElementStack.clear();
	}
}


void UIComponentMenuCaster::onEvent(Event event, UIView* view)
{

}

void UIComponentMenuCaster::onRender(GraphicsDevice* renderer, UIView* view)
{

}

NEPHILIM_NS_END