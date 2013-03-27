#ifndef UIStateContext_h__
#define UIStateContext_h__

#include "Platform.h"
#include "Vectors.h"
#include "Font.h"
#include "Localization.h"

PARABOLA_NAMESPACE_BEGIN

class UIWindow;
class UIControl;

class UIStateContext{
public:
	enum ScreenInputType
	{
		Touch,
		Mouse
	};

	UIStateContext(){
		m_allowsToolTips = true; // in mobile there are none for instance
#ifdef PARABOLA_DESKTOP
		m_screenInputType = Mouse;
#else
		m_screenInputType = Touch;
#endif

		m_fakeTouchScreen = false;

		m_fakeBackButtonWithBackSpace = false;
		m_fakeAndroidHomeWithSpace = false;
		m_fakeAndroidOptionsWithControl = false;
		m_blockHardwareKeyboard = false;

		m_focusControl = NULL;
		m_dragControl = NULL;
		m_dragOffset = Vec2f(0,0);

		m_allowLayoutAnimation = true;
		m_allowAnimation = true;

		m_defaultFont.loadFromFile("Brutality.ttf");
	}
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

PARABOLA_NAMESPACE_END
#endif // UIStateContext_h__
