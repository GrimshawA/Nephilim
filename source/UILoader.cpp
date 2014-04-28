#include <Nephilim/UILoader.h>
#include <Nephilim/UIView.h>
#include <Nephilim/UIImage.h>
#include <Nephilim/Logger.h>
#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UI/UIComponentTouchScroll.h>
#include <Nephilim/StringList.h>
#include <Nephilim/UI/UIComponentDebug.h>


NEPHILIM_NS_BEGIN

bool UILoaderXML::loadFromFile(const String& filename)
{
	pugi::xml_parse_result result = document.load_file(filename.c_str());

//	std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("view").attribute("name").value() << std::endl;

	return result;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

size_t getNodeChildrenCount(pugi::xml_node& node)
{
	size_t i = 0;
	pugi::xml_node_iterator it = node.begin();
	while(it != node.end())
	{
		++i;
		++it;
	}

	return i;
}

void configureViewFromAttributes(UIView* view, pugi::xml_node& node)
{
	if(!node.attribute("rx").empty())
	{
		view->setLocalPosition(node.attribute("rx").as_float() * view->getParent()->getSize().x, view->getLocalPosition().y);
	}
	if(!node.attribute("ry").empty())
	{
		view->setLocalPosition(view->getLocalPosition().x, node.attribute("ry").as_float() * view->getParent()->getSize().y);
	}
}

// Take the definition of the xml node and create a new UI element, attached to a given parent
void add_child_element_from_xml(UIView* parent, pugi::xml_node& newChild)
{

}

// Take a list of components and initializations and add them to the view
void processComponentsString(UIView* view, const String& str)
{

	// Process each component
	if(str.find_first_of(':') != str.npos)
	{

	}
	else
	{
		view->addComponent(str);
	}
}

void setup_view_from_node(UIView* view, pugi::xml_node& node)
{
	for(pugi::xml_attribute_iterator it = node.attributes_begin(); it != node.attributes_end(); ++it)
	{
		String attributeName = it->name();

		if(attributeName == "size")
		{
			// Its a tuple for width and height
			String tuple = it->as_string();
			StringList elems = tuple.split(',');
			if(elems.size() == 2)
			{
				float width, height;
				if(elems[0].contains("%"))
				{
					elems[0].removeCharacter('%');
					width = elems[0].toFloat();
					width /= 100.f;
					width *= view->getParent()->getSize().x;
				}
				else
				{
					width = elems[0].toFloat();
				}

				if(elems[1].contains("%"))
				{
					elems[1].removeCharacter('%');
					height = elems[1].toFloat();
					height /= 100.f;
					height *= view->getParent()->getSize().y;
				}
				else
				{
					height = elems[1].toFloat();
				}

				view->setSize(width, height);
			}
		}
		if(attributeName == "position")
		{
			// Its a tuple for width and height
			String tuple = it->as_string();
			StringList elems = tuple.split(',');
			if(elems.size() == 2)
			{
				float width, height;
				if(elems[0].contains("%"))
				{
					elems[0].removeCharacter('%');
					width = elems[0].toFloat();
					width /= 100.f;
					width *= view->getParent()->getSize().x;
				}
				else
				{
					width = elems[0].toFloat();
				}

				if(elems[1].contains("%"))
				{
					elems[1].removeCharacter('%');
					height = elems[1].toFloat();
					height /= 100.f;
					height *= view->getParent()->getSize().y;
				}
				else
				{
					height = elems[1].toFloat();
				}

				view->setLocalPosition(width, height);
			}
		}
		else if(attributeName == "components")
		{
			processComponentsString(view, it->as_string());
		}
		else if(attributeName == "debug")
		{
			// Its a tuple for a debug color
			String tuple = it->as_string();
			StringList elems = tuple.split(',');
			if(elems.size() == 3)
			{
				int r = elems[0].toInt();
				int g = elems[1].toInt();
				int b = elems[2].toInt();

				view->addComponent(new UIComponentDebugColor(Color(r,g,b)));
			}
		}
	}
}

/// Takes the XML node and adds it to view as a new child
void add_node_to_view(pugi::xml_node& node, UIView* view)
{
	// Add a new child to the view for this node
	UIView* nodeView = view->createChild(node.attribute("name").as_string("unnamed"));

	// Configure the view created from node
	Log("Added the node %s", nodeView->getName().c_str());
	setup_view_from_node(nodeView, node);

	// Continue to iterate children
	for(pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it)
	{
		add_node_to_view((*it), nodeView);
	}
}

void UILoader::configure(UIView* view, const String& filename)
{
	UILoaderXML xmlLoader;
	xmlLoader.loadFromFile(filename);

	pugi::xml_node root_node = xmlLoader.document.first_child();
	Log("Hello %s", root_node.name());

	// Iterate all the child nodes of the root to add to view
	for(pugi::xml_node_iterator it = root_node.begin(); it != root_node.end(); ++it)
	{
		add_node_to_view((*it), view);
	}
}

//////////////////////////////////////////////////////////////////////////

UIReloadComponent::UIReloadComponent(const String& file)
{
	filename = file;
}


NEPHILIM_NS_END