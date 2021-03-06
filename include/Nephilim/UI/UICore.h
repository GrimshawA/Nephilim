#ifndef NephilimUICore_h__
#define NephilimUICore_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Vector.h>
#include <Nephilim/Graphics/Font.h>
#include <Nephilim/Foundation/Localization.h>
#include <Nephilim/UI/Stylesheet.h>

NEPHILIM_NS_BEGIN

class UICanvas;
class Widget;
class GameContent;
class UIController;

class NEPHILIM_API UIDragEvent
{
public:
	vec2i dropPosition;
	Widget* dragSource;
	Widget* dragElement;
};

class NEPHILIM_API UIEventResult
{
public:
	UIEventResult()
	{
		hitControls = false;
		clickPassedThrough = true; ///< Passes through unless specified otherwise
	}

	bool hitControls;

	/// True when the click didn't hit any modal surfaces or any controls and reached the "background"
	bool clickPassedThrough;
};

/**
	\ingroup UI
	\class UICore
	\brief Set of configurations and common data shared by all controls in a hierarchy

	This acts as a central storage unit for all user interface assets, localized strings etc.

	It also holds multiple properties that are global to the UI system.

	The ones who are reflected immediately are left public, the others need to be used through accessors (get/set)
*/
class NEPHILIM_API UICore
{
public:
	/// Default construction
	UICore();

	GameContent* content;


	/// Drag components use this element to spawn the temporary element in drags
	Widget* dragElement = nullptr;
	UIController* dragElementOwner = nullptr;

	/// Anyone can use this element to spawn tooltips anytime
	Widget* toolTipElement = nullptr;

	/// To instance context menus
	Widget* contextMenuElement = nullptr;

	/// Menus (drop down boxes, menus in the bars etc)
	/// Its a stack because menus can cast other menus
	std::vector<Widget*> menuElementStack;

	/// Every UICore has a global stylesheet
	StyleSheet stylesheet;

	/// \ingroup UI
	/// \class FontResource
	/// \brief A font resource used by the UI system
	class NEPHILIM_API FontResource
	{
	public:

	};


public:

	Uint64 defaultPositionFlags;
	Uint64 defaultSizeFlags;

	enum ScreenInputType
	{
		Touch,
		Mouse
	};

	bool transformPointerCoordinates;
	vec2 realWindowSize;
	vec2 targetWindowSize;

	Font* m_defaultFont;
	ScreenInputType m_screenInputType;

	bool m_hasHardwareKeyboard;

	bool m_allowsToolTips;

	bool m_fakeTouchScreen;
	bool m_fakeBackButtonWithBackSpace;
	bool m_fakeAndroidHomeWithSpace;
	bool m_fakeAndroidOptionsWithControl;
	bool m_blockHardwareKeyboard;

	Widget* m_focusControl;
	Widget* m_dragControl;
	Vec2f m_dragOffset;

	/// Does the user interface system use animation globally?
	bool m_allowAnimation;
	bool m_allowLayoutAnimation;

	String m_activeLanguage;
};

NEPHILIM_NS_END
#endif // NephilimUICore_h__
