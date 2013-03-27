#include <Nephilim/UITreeView.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Constructs the tree view
UITreeView::UITreeView() : UIControl(), m_lineHeight(20.f)
{

};

/// Refresh the geometry of the tree view - only a position changer
void UITreeView::refreshGeometry()
{
	// Organize root items - fit all controls together
	float rel_height = 0.f;
	for(int i = 0; i < m_items.size(); i++)
	{
		// refresh the sub item so its size is correct
		m_items[i]->refreshGeometry();
		m_items[i]->setPosition(0, rel_height);
		rel_height += m_items[i]->getSize().y;
	}
};


void UITreeView::draw(Renderer* renderer)
{
	
};

bool UITreeView::onEventNotification(Event& event)
{
	return UIControl::onEventNotification(event);
};

void UITreeView::addItemUnder(const String& parent, const String& name)
{
	if(parent == "root")
	{
		m_items.push_back(new Item());
		m_items.back()->m_caption = name;
		m_items.back()->setName(name);
		m_items.back()->setSize(m_bounds.width, m_lineHeight);
		m_items.back()->m_clipChildren = true;
		m_items.back()->m_visible = true;
		m_items.back()->m_stretchForContents = true;
		m_items.back()->m_parent = this;
		addControl(m_items.back());
	}
	else
	{
		// find 
		Item* parentNode = findItem(parent);
		if(parentNode)
		{
			parentNode->addItem(name);
		}
	}

	refreshGeometry();
};

/// Find a item in the tree by its name
UITreeView::Item* UITreeView::findItem(const String& name)
{
	Item* node = NULL;
	for(int i = 0; i < m_items.size(); i++)
	{
		node = m_items[i]->findItem(name);
		if(node) return node;
	}
	return node;
}


///////////

UITreeView::Item* UITreeView::Item::findItem(const String& name)
{
	if(getName() == name) return this;
	else
	{
		// find in children
		for(int i = 0; i < getChildCount(); i++)
		{
			if(((Item*)getChild(i))->findItem(name))
				return ((Item*)getChild(i));
		}
		return NULL;
	}
};

void UITreeView::Item::onResize()
{
	// make parent height grow together if needed
	if(m_parentItem)
	{
		m_parentItem->setSize(m_parentItem->getSize().x, max(m_parentItem->getSize().y, getSize().y));
	}

	if(m_parent)
	{
		m_parent->refreshGeometry();
		cout<<"item resized, updating positioning"<<endl;
	}
	else
	{
		cout<<"no parent?"<<endl;
	}
}

void UITreeView::Item::addItem(const String& name)
{
	Item* item = new Item();
	item->m_caption = name;
	item->setName(name);
	item->advance = advance + 50;
	item->m_stretchForContents = true;
	item->m_drawBorder = false;
	item->m_clipChildren = true;
	item->m_parent = this->m_parent;
	item->setSize(getSize().x, 20);
	addControl(item);
};

float UITreeView::Item::getItemHeight()
{
	return 20;
}

void UITreeView::Item::refreshGeometry()
{
	// Organize root items - fit all controls together
	float rel_height = 0.f;
	float finalSize = 20.f; // at least 20 pixels height
	for(int i = 0; i < getChildCount(); i++)
	{
		Item* item = (Item*)getChild(i);

		// now refresh that item too
		item->refreshGeometry();
		/// stretch for children
		finalSize += item->getSize().y;
		item->setPosition(0, m_bounds.top + 20 + rel_height);
		rel_height += item->getSize().y;
	}
};

/// Expans the item if possible
void UITreeView::Item::expand()
{
	for(int i = 0; i < getChildCount(); i++)
	{
		getChild(i)->m_visible = true;
	}

	m_expanded = true;
	setSize(getSize().x, 20);
	resize(getSize().x, getContentBounds().height, 2.0f);

	// just starting to expand again
};

void UITreeView::Item::collapse()
{
	for(int i = 0; i < getChildCount(); i++)
	{
		getChild(i)->m_visible = false;
	}

	m_expanded = false;
	setSize(getSize().x, getContentBounds().height);
	resize(getSize().x, 20, 2.0f);
};


bool UITreeView::Item::onEventNotification(Event& event){
	if(event.type == Event::MouseButtonPressed)
	{
		if(FloatRect(m_bounds.left, m_bounds.top, m_bounds.width, 20.f).contains(event.mouseButton.x, event.mouseButton.y)){
			cout<<"Hit!"<<endl;
			if(event.mouseButton.button == Mouse::Left)
				expand();
			if(event.mouseButton.button == Mouse::Right)
				collapse();
		}
		else
		{
			cout<<"no hit"<<endl;
		}
	}

	return UIControl::onEventNotification(event);
};

void UITreeView::Item::draw(Renderer* renderer)
{
	Text t;
	t.setPosition(m_bounds.left + advance, m_bounds.top);
	t.setString(m_caption);
	t.setCharacterSize(20);
	renderer->draw(t);

	if(getChildCount() > 0)
	{
		// draw expander as there are child
		if(m_expanded)
			renderer->drawDebugCircle(Vec2f(t.getPosition().x - 8, t.getPosition().y + t.getLocalBounds().height/2), 3, Vec2f(), Color::White);
		else
			renderer->drawDebugCircle(Vec2f(t.getPosition().x - 8, t.getPosition().y + t.getLocalBounds().height/2), 3, Vec2f(), Color::Red);
		
	}
}
PARABOLA_NAMESPACE_END