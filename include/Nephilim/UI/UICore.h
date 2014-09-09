#ifndef NephilimUICore_h__
#define NephilimUICore_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Font.h>
#include <Nephilim/Localization.h>

NEPHILIM_NS_BEGIN

class UICanvas;
class UIView;
class ContentManager;

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

	ContentManager* content;


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

	LocalizationUnit m_localization;

	bool m_allowsToolTips;

	bool m_fakeTouchScreen;
	bool m_fakeBackButtonWithBackSpace;
	bool m_fakeAndroidHomeWithSpace;
	bool m_fakeAndroidOptionsWithControl;
	bool m_blockHardwareKeyboard;

	UIView* m_focusControl;
	UIView* m_dragControl;
	Vec2f m_dragOffset;

	/// Does the user interface system use animation globally?
	bool m_allowAnimation;
	bool m_allowLayoutAnimation;

	String m_activeLanguage;
};

NEPHILIM_NS_END
#endif // NephilimUICore_h__
