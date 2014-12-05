#include <Nephilim/UI/UIComponentMenu.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Logger.h>

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
	Log("OPENING MENU");
	mParent->getChild(0)->show();
}


void UIComponentMenuCaster::onEvent(Event event, UIView* view)
{

}

void UIComponentMenuCaster::onRender(GraphicsDevice* renderer, UIView* view)
{

}

NEPHILIM_NS_END