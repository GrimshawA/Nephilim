#include <Nephilim/UI/UILoaderXML.h>
#include <Nephilim/UI/UIImage.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/UI/UIComponentTouchScroll.h>
#include <Nephilim/Foundation/StringList.h>

//#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIButton.h>

#include <pugixml/pugixml.hpp>


//test
#include <Nephilim/Animation/AnimationZ.h>

/*
	<img> elements are instanced as UIView's with image components
	<button> elements are instanced as UIViews with button components	
*/

NEPHILIM_NS_BEGIN

namespace
{
	/// Extract the parameters from node and apply to the view
	void process_general_params(pugi::xml_node& node, Widget* view)
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

//					view->addController(new UIDebugWidget(Color(r, g, b)));
				}
			}
			// Check if we have a layouter
			else if (attributeName == "layout")
			{
			
			}
		}
	}

	/// Process all data in the node to properly spawn the new UIView, attach it and do all configurations
	/// Returns the spawned object, or nullptr if not applicable or failed (the setup won't continue down the hierarchy)
	Widget* process_spawn(pugi::xml_node& node, Widget* parent)
	{
		Widget* v = nullptr;
		
		// Let's spawn
		if (String(node.name()) == "img")
		{
			v = parent->createChild("1");
			v->setSize(500.f, 300.f);

			String imageResource = node.attribute("src").as_string("");
			imageResource = "Ui/" + imageResource;
			//v->addController(new UIComponentImage(imageResource));
		}
		else if (String(node.name()) == "button")
		{
			v = parent->createChild("1");
			v->setSize(500.f, 300.f);

			//v->addComponent(new UIComponentButton(node.attribute("label").as_string("none")));
		}
		else if (String(node.name()) == "text")
		{
			v = parent->createChild("1");
			v->setSize(100.f, 40.f);

			//v->addController(new UITextNode(node.attribute("content").as_string("none")));
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
	void process_node(pugi::xml_node& node, Widget* parent)
	{
		if (!parent)
			return;

		Log("Processing node %s", node.name());

		Widget* spawnView = process_spawn(node, parent);	

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
bool UILoaderXML::loadFromFile(const String& filename, Widget* root_view)
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


//////////////////////////////////////////////////////////////////////////


/// Just a test function, needs api changes
Animation* UIAnimationLoaderXML::load(const String& filename, Widget* source_widget)
{
	Animation* anim = nullptr;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.c_str());

	if (result)
	{
		pugi::xml_node root = doc.child("Animation");
		
		for (auto& n : root)
		{
			Log("FOUND NODE: %s", n.name());
			if (String(n.name()) == "ZAnim")
			{
				anim = new AnimationZ(n.attribute("to").as_float(0.f), n.attribute("duration").as_float(1.f));
				static_cast<AnimationZ*>(anim)->setZCallback.connect(sigc::mem_fun(source_widget, &Widget::setZ));
			}			
		}
	}

	return anim;
}

NEPHILIM_NS_END