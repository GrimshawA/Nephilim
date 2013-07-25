#include <Nephilim/UIBoxLayout.h>
#include <Nephilim/UIControl.h>
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


void UIBoxLayout::doLayout(UIControl* parent)
{
	if(!parent)return;

	if(m_orientation == UILayout::Vertical)
	{
		float spaceToGive = parent->getSize().y;
		float currentEvenSpace = spaceToGive / parent->getChildCount();
		float parentWidth = parent->getSize().x;
		int childLeft = parent->getChildCount();
		float currentPosition = parent->getBounds().top;

		for(int i = 0; i < parent->getChildCount(); i++)
		{
			UIControl* child = parent->getChild(i);

			// compute final size
			Vec2f finalSize;
			finalSize.x = parentWidth;
			finalSize.y = currentEvenSpace;

			// check rules
			if(i == 0)finalSize.y = 100;

			// recompute even space if needed
			spaceToGive -= finalSize.y;
			childLeft--;
			currentEvenSpace = spaceToGive / childLeft;

			Vec2f finalPosition;
			finalPosition.x = parent->getBounds().left;
			finalPosition.y = currentPosition;

			currentPosition += finalSize.y;

			if(m_animated)
			{	
		
				child->resize(finalSize.x, finalSize.y, 1.f);
			}
			else
			{
				// make it full width and distribute height
				child->setSize(finalSize.x, finalSize.y);
				// align left and distribute
				child->setPosition(finalPosition.x, finalPosition.y);
			}
		}
	}
	else
	{
		for(int i = 0; i < parent->getChildCount(); i++)
		{
			UIControl* child = parent->getChild(i);

			if(m_animated)
			{	
			//	child->reposition(parent->getBounds().left + (parent->getSize().x / parent->getChildCount() * i), parent->getBounds().top, 1.f);
				child->resize(parent->getSize().x / parent->getChildCount(), parent->getSize().y, 1.f);
			}
			else
			{
				// make it full width and distribute height
				child->setSize(parent->getSize().x / parent->getChildCount(), parent->getSize().y );
				// align left and distribute
				child->setPosition(parent->getBounds().left + (parent->getSize().x / parent->getChildCount() * i), parent->getBounds().top);
			}
		}
	}

	cout<<"Layouting: "<<parent->getChildCount()<<endl;
};

NEPHILIM_NS_END