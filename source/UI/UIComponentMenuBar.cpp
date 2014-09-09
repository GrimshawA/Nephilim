#include <Nephilim/UI/UIComponentMenuBar.h>
#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UI/UIComponentMenu.h>
#include <Nephilim/UI/UIComponentButton.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/UI/UIComponentTouchScroll.h>
#include <Nephilim/UI/UIComponentText.h>
#include <Nephilim/UI/UIComponentDebug.h>


NEPHILIM_NS_BEGIN

UIComponentMenuBar::UIComponentMenuBar()
{

}

void UIComponentMenuBar::onAttach(UIView* view)
{
	mParent = view;

	addMenu("File");
	addMenu("View");
	addMenu("Help");
}

void UIComponentMenuBar::addMenu(const String& menuTitle)
{
	UIView* fileMenu = new UIView();
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
	fileMenuContainer->addComponent(new UIComponentMenu);
	fileMenu->attach(fileMenuContainer);

	// Add one sample option..
	UIView* exitAction = new UIView();
	exitAction->addComponent(new UIComponentButton );
	//exitAction->addComponent(new UIComponentText("Exit", UIComponentText::Left, UIComponentText::Center) );
	exitAction->onClick.connect(sigc::bind(sigc::mem_fun(this, &UIComponentMenuBar::meteNojo), "SAAAAAAi"));
	fileMenuContainer->attach(exitAction);
	exitAction->setLocalPosition(0.f, 0.f);
	exitAction->setSize(150.f, 20.f);
}

void UIComponentMenuBar::meteNojo(const String &name)
{
	Log("Nojo: %s", name.c_str());
}

void UIComponentMenuBar::openMenu(const String& name)
{
	if(mParent->findByName(name))
	{
		UIView* fileMenu = mParent->findByName(name);
		if(fileMenu)
		{
			// The menu exists
			UIView* dropDownMenu = fileMenu->getChild(0);
			dropDownMenu->m_visible = ! dropDownMenu->m_visible;			
		}
	}
}


void UIComponentMenuBar::onEvent(Event event, UIView* view)
{

}

void UIComponentMenuBar::onRender(Renderer* renderer, UIView* view)
{

}

NEPHILIM_NS_END