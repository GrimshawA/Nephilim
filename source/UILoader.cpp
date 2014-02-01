#include <Nephilim/UILoader.h>
#include <Nephilim/UIView.h>
#include <Nephilim/UIImage.h>
#include <Nephilim/Logger.h>
#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UIScroller.h>

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
//	cout << "Adding a child to a UIView from tag " << newChild.name() << endl;
	String tag = newChild.name();

	UIView* generatedView = NULL;
	// Lets prepare our new control
	if(tag == "img")
	{
		// this is an image, lets prepare the UI node
		UIImage* imageView = new UIImage();
		imageView->t.loadFromFile(newChild.attribute("src").as_string());
		parent->attach(imageView);

		// lets prepare the size & position
		vec2 size(0.f, 0.f);
		vec2 position(0.f, 0.f);
		if(!newChild.attribute("rwidth").empty())
		{
			size.x = newChild.attribute("rwidth").as_float();
			size.x *= parent->getSize().x;
		}
		if(!newChild.attribute("rheight").empty())
		{
			size.y = newChild.attribute("rheight").as_float();
			size.y *= parent->getSize().y;
		}
		if(!newChild.attribute("rx").empty())
		{
			position.x = newChild.attribute("rx").as_float();
			position.x *= parent->getSize().x;
		}
		if(!newChild.attribute("ry").empty())
		{
			position.y = newChild.attribute("ry").as_float();
			position.y *= parent->getSize().y;
		}

		imageView->setSize(size.x, size.y);
		imageView->setLocalPosition(position);

		generatedView = imageView;
	}
	else
	{
		// -- handling a component node
		if(tag == "cdata")
		{
			Log("====> Adding Component");

		}
		// -- handling a child node
		else 
		{
			Log("====> Adding Child");

			if(tag == "text")
			{	
				generatedView = new UIView(parent);
				//generatedView->setSize(300.f,300.f);
				//generatedView->addComponent(new UIComponentDebugColor);
				generatedView->addComponent(new UIComponentText(newChild.text().as_string(), UIComponentText::Left, UIComponentText::Left));
				configureViewFromAttributes(generatedView, newChild);
			}
		}
	}

	// Now iterate the node children again and keep the hierarchy going
	for(pugi::xml_node_iterator it = newChild.begin(); it != newChild.end(); ++it)
	{
		add_child_element_from_xml(generatedView, (*it));
	}
}

void xml_to_uiview(pugi::xml_document& document, UIView* view)
{
	pugi::xml_node root_view = document.first_child();

	//cout << "Our element will have " << getNodeChildrenCount(root_view) << " sub elements" << endl;

	for(pugi::xml_node_iterator it = root_view.begin(); it != root_view.end(); ++it)
	{
		add_child_element_from_xml(view, (*it));
	}
}

void UILoader::configure(UIView* view, const String& filename)
{
	UILoaderXML xmlLoader;
	xmlLoader.loadFromFile(filename);

	xml_to_uiview(xmlLoader.document, view);
}

//////////////////////////////////////////////////////////////////////////

UIReloadComponent::UIReloadComponent(const String& file)
{
	filename = file;
}


NEPHILIM_NS_END