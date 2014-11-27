#include <Nephilim/UI/UIBoxLayout.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Logger.h>
#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Default construction
/// By default the orientation is set as Vertical and no animation
UIBoxLayout::UIBoxLayout() : m_orientation(UILayout::Vertical), m_animated(false)
{

};

UIBoxLayout::UIBoxLayout(UILayout::Orientation orientation, bool animated)
	:	m_orientation(orientation),
		m_animated(animated)
{

}


void UIBoxLayout::doLayout(UIView* parent)
{

	if(!parent)return;

	if(m_orientation == UILayout::Vertical)
	{
		float latestY = 0.f;
		for (std::size_t i = 0; i < parent->getChildCount(); ++i)
		{
			// simply put the view below where the previous ends
			UIView* child = parent->getChild(i);

			child->setPosition(0.f, latestY);

			latestY += child->getSize().y;
		}
	}
	else
	{
		float latestX = parent->getPosition().x;
		for (std::size_t i = 0; i < parent->getChildCount(); ++i)
		{
			// simply put the view below where the previous ends
			UIView* child = parent->getChild(i);
			child->setPosition(latestX, parent->getPosition().y);

			latestX += child->getSize().x;
		}
	}
};

NEPHILIM_NS_END