#include <Nephilim/UI/UIListPanel.h>
#include <Nephilim/UI/UxEvent.h>
#include <Nephilim/UI/UIScrollBar.h>

#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

/// Initial setup
void UIListPanel::onSetup()
{
	UIScrollBar* scrollBar = createChild<UIScrollBar>("scrolly");
	scrollBar->setSize(20.f, 200.f);
	//scrollBar->setPosition(400.f, 0.f);
	scrollBar->linkedView = this;
}

/// Called on the subclass when a new child is added
void UIListPanel::onChildAdded(Widget* widget)
{
	Log("Adding");
}

/// Intercept the events to handle them
void UIListPanel::dispatch(const UxEvent& event)
{
	Log("EVENT!");

	// One children just changed size, we need to adapt this container
	if (event.type == 1)
	{
		// first, make sure its size is appropriate for the scroll bar
		//static_cast<UIView*>(event.emitter)->size.x = width() - 20.f;

		bool found = false;
		for (std::size_t i = 0; i < mChildren.size(); ++i)
		{
			if (mChildren[i] == event.emitter)
				found = true;

			if (found)
			{
				if (i == 0)
				{
					static_cast<Widget*>(mChildren[i])->setPosition(0.f, 0.f);
				}
				else
					static_cast<Widget*>(mChildren[i])->setPosition(0.f, static_cast<Widget*>(mChildren[i - 1])->getPosition().y + static_cast<Widget*>(mChildren[i - 1])->height());
			}
		}
	}
}

void UIListPanel::refresh()
{
	float t = 0.f;
	for (auto& c : mChildren)
	{
		static_cast<Widget*>(c)->setPosition(0.f, t);
		
		t += static_cast<Widget*>(c)->getSize().y;
	}
}

NEPHILIM_NS_END