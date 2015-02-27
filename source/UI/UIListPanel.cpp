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
void UIListPanel::onChildAdded(UIView* widget)
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
		for (std::size_t i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i] == event.emitter)
				found = true;

			if (found)
			{
				if (i == 0)
				{
					m_children[i]->setPosition(0.f, 0.f);
				}
				else
					m_children[i]->setPosition(0.f, m_children[i - 1]->getPosition().y + m_children[i - 1]->height());
			}
		}
	}
}

void UIListPanel::refresh()
{
	float t = 0.f;
	for (auto& c : m_children)
	{
		c->setPosition(0.f, t);
		
		t += c->getSize().y;
	}
}

NEPHILIM_NS_END