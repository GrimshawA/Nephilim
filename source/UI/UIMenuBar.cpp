#include <Nephilim/UI/UIMenuBar.h>
#include <Nephilim/UI/UIMenu.h>
#include <Nephilim/UI/UIButton.h>
#include <Nephilim/UI/Widget.h>
#include <Nephilim/UI/UIComponentTouchScroll.h>
#include <Nephilim/UI/UITextNode.h>
//#include <Nephilim/UI/UIComponentDebug.h>


NEPHILIM_NS_BEGIN

UIMenuBar::UIMenuBar()
{

}

void UIMenuBar::onAttach(Widget* view)
{
	mParent = view;

	addMenu("File");
	addMenu("View");
	addMenu("Help");
}

void UIMenuBar::addMenu(const String& menuTitle)
{
	/*UIView* fileMenu = new UIView();
	fileMenu->setName(menuTitle);
	fileMenu->setRect(mParent->getPosition().x + 60.f * mParent->getChildCount(), mParent->getPosition().y, 60.f, 30.f);
	fileMenu->addComponent(new UIComponentButton(menuTitle) );
	fileMenu->getComponent<UIComponentButton>()->mNormalColor = Color::Transparent;
	//fileMenu->addComponent(new UIComponentText(menuTitle, UIComponentText::Center, UIComponentText::Center) );
	fileMenu->onClick.connect(sigc::bind(sigc::mem_fun(this, &UIComponentMenuBar::openMenu), menuTitle));
	mParent->attach(fileMenu);

	// Now the menu is in place, lets add its actual open contents
	UIView* fileMenuContainer = new UIView();
	fileMenuContainer->hide();
	fileMenuContainer->setRect(5.f, 32.f, 150.f, 300.f);
	fileMenuContainer->addComponent(new UIComponentDebugColor(Color(31,31,31)));
	fileMenuContainer->addComponent(new UIComponentMenuCaster);
	fileMenu->attach(fileMenuContainer);

	// Add one sample option..
	UIView* exitAction = new UIView();
	exitAction->addComponent(new UIComponentButton );
	//exitAction->addComponent(new UIComponentText("Exit", UIComponentText::Left, UIComponentText::Center) );
	exitAction->onClick.connect(sigc::bind(sigc::mem_fun(this, &UIComponentMenuBar::meteNojo), "SAAAAAAi"));
	fileMenuContainer->attach(exitAction);
	exitAction->setLocalPosition(0.f, 0.f);
	exitAction->setSize(150.f, 20.f);*/
}

void UIMenuBar::meteNojo(const String &name)
{
	Log("Nojo: %s", name.c_str());
}

void UIMenuBar::openMenu(const String& name)
{
	if(mParent->findByName(name))
	{
		Widget* fileMenu = mParent->findByName(name);
		if(fileMenu)
		{
			// The menu exists
			Widget* dropDownMenu = fileMenu->getChild(0);
			dropDownMenu->m_visible = ! dropDownMenu->m_visible;			
		}
	}
}


void UIMenuBar::onEvent(Event event, Widget* view)
{

}

void UIMenuBar::onRender(GraphicsDevice* renderer, Widget* view)
{

}

NEPHILIM_NS_END