#ifndef NephilimUIControl_h__
#define NephilimUIControl_h__

#include "Platform.h"
#include "Rect.h"
#include "Event.h"
#include "Signals.h"
#include "Strings.h"
#include "RectangleShape.h"
#include "Renderer.h"
#include "RefCount.h"
#include "AxList.h"
#include "AxTarget.h"
#include <vector>

#include "UISizePolicy.h"
#include "UILayout.h"
#include "UICore.h"
#include "Matrix.h"

NEPHILIM_NS_BEGIN

class AxBase;
class ASSlot;

namespace UIPositionFlag
{
	enum Flags
	{
		AttachBottom = 1 << 0,
		AttachRight = 1 << 1,
		KeepRelativePositionX = 1 << 2,
		KeepRelativePositionY = 1 << 3
	};
}

namespace UISizeFlag
{
	enum Flags
	{
		KeepRelativeSizeX = 1 << 0,
		KeepRelativeSizeY = 1 << 1
	};
}

class NEPHILIM_API UIEventResult
{
public:
	bool hitControls;
};

class NEPHILIM_API UIControl : public AxTarget, public sigc::trackable, public Animable, public RefCountable
{
public:
	friend class UILayout;

	/// Base constructor of controls
	UIControl();

	virtual ~UIControl(){ }

	/// Get the coordinates of the top-left corner of the control
	vec2 getPosition();

	/// Get the parent control
	UIControl* getParent();

	/// Adds a child control
	void attach(UIControl* control);

	/// Submit an animation to be processed by the control
	void commitAnimation(AxBase* animation);

	/// Set a new layout to the control
	void setLayout(UILayout* layout);

	/// Set positioning flags to the control
	void setPositionFlags(Uint64 flags);

	/// Get the current positioning flags
	Uint64 getPositionFlags();

	/// Check the existence of a particular flag for positioning
	bool hasPositionFlag(Uint64 flag);

	/// Set the flags for sizing
	void setSizeFlags(Uint64 flags);

	/// Get the sizing flags
	Uint64 getSizeFlags();

	/// Check if there is a particular sizing flag
	bool hasSizeFlag(Uint64 flag);

	/// Get the currently assigned layout controller
	/// \return NULL if there is no layout controller assigned
	UILayout* getLayout();

	/// Get the number of children of this control
	int getChildCount();

	/// Is the control able to get input focus or not?
	virtual bool isFocusable();

	/// Check if the control currently has focus
	bool hasFocus();

	/// Attempts focus on this control
	bool focus();

	/// Remove focus from the element
	void blur();

	/// Get a child at a index
	UIControl* getChild(int index);

	/// Get the current size of the control
	Vec2f getSize();

	/// Get the bounding rect of this control and all its children
	FloatRect getContentBounds();

	/// Returns the UIWindow context or NULL if not attached
	UICore* getContext();

	/// Returns true when the control is subject of being layout in a grid or other organization form
	/// Most controls don't implement this function, as their default behavior is to respond to layouts always
	virtual bool respondsToLayouts();

	/// Requests a tool tip text label from the control
	/// If only a empty string is returned, no tooltip is shown
	virtual String getToolTipLabel();

	void innerDraw(Renderer* renderer, const mat4& transform = mat4());

	/// Callback to render itself, renders children
	virtual void draw(Renderer* renderer);

	/// Callback to handle events
	virtual bool onEventNotification(Event& event);


	/// Attempt to process positional flags
	virtual void processPositionFlags();

	/// Attempt to process size flags
	virtual void processSizeFlags();

	/// Process a mouve movement event
	/// Returns false if the mouse isnt on any control
	virtual bool processMouseMove(int x, int y);

	/// Process a mouse press event
	bool processMouseButtonPressed(int x, int y, Mouse::Button button);

	virtual bool onKeyPressed(Keyboard::Key key);
	virtual bool onTextEvent(Uint32 code);

	virtual void onAttach(){}

	/// Callback when the control is resized
	virtual void onResize();

	virtual void bindSignal(const String& name, ASSlot* slot);

	template<typename T>
	void setProperty(const String& propertyName, const T& propertyValue);

	/// Immediately sets the new size of the control 
	void setSize(float width, float height);

	/// Set the proportion of the control , relative to its parent
	void setProportion(float widthFactor, float heightFactor);

	/// Set the placement proportion of the control
	void setPlacement(float xFactor, float yFactor);

	/// Immediately sets the center of the control to a new position
	void setCenter(float x, float y);

	/// Immediately sets the center of the control to a new position
	void setCenter(Vec2f position);

	/// Set the position of the control
	void setPosition(float x, float y);

	/// Define a new name for this control
	void setName(const String& name);

	/// Deep clone of the control and its hierarchy
	virtual UIControl* clone();

	/// Called to re adjust children positions and sizes if needed
	virtual void processSizeChange(float previousWidth, float previousHeight);

	/// Get bounds of the control
	FloatRect getBounds();

	/// Get the name of the control
	String getName();

	/// Update the control
	void onUpdate(float elapsedTime);

	/// Update layout of children
	void updateLayout();

	void setRect(FloatRect rect);

	FloatRect getRect();

	void switchLanguage();

	virtual void innerLanguageSwitch(){}

	Vec2f getMiddlePosition();

	/// Resizes the control over a defined time
	/// The lower border of the control will become at target position
	void resizeToPoint(float x, float y, float duration);

	void resize(float width, float height, float duration);

	void reposition(float x, float y, float duration);

	/// Enables or disables a pseudo class
	void setPseudoClass(const String& name, bool active);

	/// Feeds the position of the control to the animation systems
	virtual vec2 axGetPosition2D();

	virtual void axSetPosition2D(vec2 position);

	virtual void axSetAlpha(float alpha);

	virtual float axGetAlpha();

	/// Signal emitted whenever the slider value changes
	sigc::signal<void, int> onValueChanged;

	/// Events fired by the control
	sigc::signal<void> onMouseEnter;
	sigc::signal<void> onMouseLeave;
	sigc::signal<void> onMouseMove;
	sigc::signal<void> onClick;
	sigc::signal<void> onDoubleClick;
	sigc::signal<void> onTripleClick;
	sigc::signal<void> onSizeChanged;
	sigc::signal<void> onFocus;
	sigc::signal<void> onLostFocus;

	UICore* m_stateContext;

	/// Hierarchicly sets the context to all children
	void setContext(UICore* states);

	bool m_clipContents; ///< Whether the contents of the control itself are clipped at the border
	bool m_clipChildren; ///< Whether the children are clipped on the control rectangle
	/// Is the control being rendered?
	bool m_visible;
	bool m_stretchForContents;
	bool m_drawBorder; /// temp

	UISizePolicy m_sizePolicy;
	UISizePolicy m_positionPolicy;

	Uint64 m_positionFlags;
	Uint64 m_sizeFlags;

	/// Reload all graphics because they were destroyed and are unavailable now
	virtual void reloadGraphicalAssets();


	/// Cascaded transform
	mat4 m_transform;

	AxList m_animations; ///< Animation list

protected: // functions

	/// Callback when the position of the control changed, for updating nested objects
	virtual void onPositionChanged();


protected:
	/// The bounds of the control, if scissor tests are enabled, nothing is drawn outside this rect
	Rect<float> m_bounds;
	RectangleShape m_background;


	Vec2f m_minimumDimensions;
	Vec2f m_maximumDimensions;

	bool m_hasFocus;

	bool m_hovered;


	Color m_backgroundColor;
	Color m_topBorderColor, m_bottomBorderColor, m_leftBorderColor, m_rightBorderColor;

	/// The layout controller for this control
	UILayout* m_layoutController;

	/// Unique name of the control in the hierarchy
	String m_name;

	/// Children of the control
	std::vector<UIControl*> m_children;

	/// Parent of the control, if any
	UIControl* m_parent;


	/// Making this class able to animate sizes
	virtual void animable_set_size(float x, float y);
	virtual Vec2f animable_get_size();
	virtual void animable_set_position(float x, float y);
	virtual Vec2f animable_get_position();
};

template<typename T>
void UIControl::setProperty(const String& propertyName, const T& propertyValue)
{
	if(propertyName == "background-color")
	{
		m_backgroundColor = propertyValue;
		return;
	}
	else if(propertyName == "border-top-color")
	{
		m_topBorderColor = propertyValue;
	}
	else if(propertyName == "border-bottom-color")
	{
		m_bottomBorderColor = propertyValue;
	}
	else if(propertyName == "border-left-color")
	{
		m_leftBorderColor = propertyValue;
	}
	else if(propertyName == "border-right-color")
	{
		m_rightBorderColor = propertyValue;
	}
};

NEPHILIM_NS_END
#endif // NephilimUIControl_h__
