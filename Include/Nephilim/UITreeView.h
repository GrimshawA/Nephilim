#ifndef UITreeView_h__
#define UITreeView_h__

#include "Platform.h"
#include "UIControl.h"
#include "Text.h"

#include <vector>

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API UITreeView : public UIControl
{
public:
	/// Constructs the tree view
	UITreeView();

	/// Refresh the geometry of the tree view
	void refreshGeometry();

	





	void draw(Renderer* renderer);
	bool onEventNotification(Event& event);

	/// A node in the tree
	class Item : public UIControl
	{
	public:
		Item() : UIControl(), m_parent(NULL), m_parentItem(NULL){
			advance = 10;
			m_visible = false;
			m_expanded = false;
			setProperty<Color>("background-color", Color(0,0,0,0));
		}
		void draw(Renderer* renderer);
		bool onEventNotification(Event& event);

		/// Expans the item if possible
		void expand();

		void collapse();

		void onResize();

		float getItemHeight();

		void refreshGeometry();

		Item* findItem(const String& name);
		void addItem(const String& name);

		UITreeView* m_parent;
		Item* m_parentItem;
		bool m_expanded;
		String m_caption;
		std::vector<Item*> children;
		Text m_text;
		float advance;
	};
	/// Find a item in the tree by its name
	Item* findItem(const String& name);
	
	void addItemUnder(const String& parent, const String& name);

	/// The list of items to draw
	std::vector<Item*> m_items;

	float m_lineHeight;
};

/// Typedefs
typedef UITreeView::Item UITreeViewItem;

PARABOLA_NAMESPACE_END
#endif // UITreeView_h__
