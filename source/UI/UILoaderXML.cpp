#include <Nephilim/UI/UILoaderXML.h>
#include <Nephilim/UI/UIImage.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UI/UIComponentTouchScroll.h>
#include <Nephilim/Foundation/StringList.h>

#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIComponentButton.h>
#include <Nephilim/UI/UIComponentText.h>

#include <Nephilim/UI/UIBoxLayout.h>

#include <pugixml/pugixml.hpp>

/*
	<img> elements are instanced as UIView's with image components
	<button> elements are instanced as UIViews with button components	
*/

NEPHILIM_NS_BEGIN

namespace
{
	// Take a list of components and initializations and add them to the view
	void processComponentsString(UIView* view, const String& str)
	{
		// Process each component
		if (str.find_first_of(':') != str.npos)
		{

		}
		else
		{
			view->addComponent(str);
		}
	}

	/// Extract the parameters from node and apply to the view
	void process_general_params(pugi::xml_node& node, UIView* view)
	{
		for (pugi::xml_attribute_iterator it = node.attributes_begin(); it != node.attributes_end(); ++it)
		{
			String attributeName = it->name();

			if (attributeName == "id")
			{
				view->setName(it->as_string());
			}
			if (attributeName == "size")
			{
				// Its a tuple for width and height
				String tuple = it->as_string();
				StringList elems = tuple.split(',');
				if (elems.size() == 2)
				{
					float width, height;
					if (elems[0].contains("%"))
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

					if (elems[1].contains("%"))
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
			if (attributeName == "position")
			{
				// Its a tuple for width and height
				String tuple = it->as_string();
				StringList elems = tuple.split(',');
				if (elems.size() == 2)
				{
					float width, height;
					if (elems[0].contains("%"))
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

					if (elems[1].contains("%"))
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
					Log("position set to %f, %f", width, height);
				}
			}
			else if (attributeName == "components")
			{
				processComponentsString(view, it->as_string());
			}
			else if (attributeName == "debug")
			{
				// Its a tuple for a debug color
				String tuple = it->as_string();
				StringList elems = tuple.split(',');
				if (elems.size() == 3)
				{
					int r = elems[0].toInt();
					int g = elems[1].toInt();
					int b = elems[2].toInt();

					view->addComponent(new UIComponentDebugColor(Color(r, g, b)));
				}
			}
			// Check if we have a layouter
			else if (attributeName == "layout")
			{
				String layout_string = it->as_string("");

				Log("LAYOUT: %s", it->as_string());
				if (layout_string == "box_h")
				{
					view->setLayout(new UIBoxLayout(UIBoxLayout::Horizontal, false));
				}
				if (layout_string == "box_v")
				{
					view->setLayout(new UIBoxLayout(UIBoxLayout::Vertical, false));

				}
			}
		}
	}

	/// Process all data in the node to properly spawn the new UIView, attach it and do all configurations
	/// Returns the spawned object, or nullptr if not applicable or failed (the setup won't continue down the hierarchy)
	UIView* process_spawn(pugi::xml_node& node, UIView* parent)
	{
		UIView* v = nullptr;
		
		// Let's spawn
		if (String(node.name()) == "img")
		{
			v = parent->createChild("1");
			v->setSize(500.f, 300.f);

			String imageResource = node.attribute("src").as_string("");
			imageResource = "Ui/" + imageResource;
			v->addComponent(new UIComponentImage(imageResource));
		}
		else if (String(node.name()) == "button")
		{
			v = parent->createChild("1");
			v->setSize(500.f, 300.f);

			v->addComponent(new UIComponentButton(node.attribute("label").as_string("none")));
		}
		else if (String(node.name()) == "text")
		{
			v = parent->createChild("1");
			v->setSize(100.f, 40.f);

			v->addComponent(new UIComponentText(node.attribute("content").as_string("none")));
		}
		else
		{
			v = parent->createChild("1");
		}

		// 2. Processing step (only if we have a new view)
		if (v)
		{
			process_general_params(node, v);
		}

		// 3. Style the view with the stylesheet
		if (v)
		{
			v->updateStyles();
		}

		return v;
	}

	/// Process the node, instantiate widgets and components and add it to parent properly
	void process_node(pugi::xml_node& node, UIView* parent)
	{
		if (!parent)
			return;

		Log("Processing node %s", node.name());

		UIView* spawnView = process_spawn(node, parent);	

		if (!spawnView)
			return;

		// Children of this node will be associated with its parent
		for (auto it = node.children().begin(); it != node.children().end(); ++it)
		{
			process_node((*it), spawnView);
		}
	}

};

/// Load the xml file into the node
bool UILoaderXML::loadFromFile(const String& filename, UIView* root_view)
{
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_file(filename.c_str());

	if (result)
	{
		pugi::xml_node body_node = document.child("body");
		if (body_node)
		{
			// Children of the body become children of root_view
			for (auto it = body_node.children().begin(); it != body_node.children().end(); ++it)
			{
				process_node((*it), root_view);
			}
		}
	}
	else
	{
		std::cout << "Load result: " << result.description() << std::endl;
	}

	return result;
}

NEPHILIM_NS_END