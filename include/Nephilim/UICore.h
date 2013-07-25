#ifndef NephilimUICore_h__
#define NephilimUICore_h__

#include "Platform.h"
#include "Vectors.h"
#include "Font.h"
#include "Localization.h"

NEPHILIM_NS_BEGIN

class UIDocument;
class UIControl;

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
	\brief Represents the core of a user interface system

	This acts as a central storage unit for all user interface assets, localized strings etc.

	It also holds multiple properties that are global to the UI system.

	The ones who are reflected immediately are left public, the others need to be used through accessors (get/set)
*/
class NEPHILIM_API UICore
{
public:
	/// Construct the basic settings of the core automatically
	UICore();

	/// \ingroup UI
	/// \class TextureResource
	/// \brief A texture resource used by the UI system
	class NEPHILIM_API TextureResource
	{
	public:

	};


	/// \ingroup UI
	/// \class FontResource
	/// \brief A font resource used by the UI system
	class NEPHILIM_API FontResource
	{
	public:

	};

private:
	std::map<String, FontResource*>    m_fonts;    ///< All fonts shared by the UI system
	std::map<String, TextureResource*> m_textures; ///< All textures shared by the UI system



public:


	enum ScreenInputType
	{
		Touch,
		Mouse
	};


	Font m_defaultFont;
	ScreenInputType m_screenInputType;

	bool m_hasHardwareKeyboard;

	LocalizationUnit m_localization;

	bool m_allowsToolTips;

	bool m_fakeTouchScreen;
	bool m_fakeBackButtonWithBackSpace;
	bool m_fakeAndroidHomeWithSpace;
	bool m_fakeAndroidOptionsWithControl;
	bool m_blockHardwareKeyboard;

	UIControl* m_focusControl;
	UIControl* m_dragControl;
	Vec2f m_dragOffset;

	/// Does the user interface system use animation globally?
	bool m_allowAnimation;
	bool m_allowLayoutAnimation;

	String m_activeLanguage;
};

NEPHILIM_NS_END
#endif // NephilimUICore_h__
