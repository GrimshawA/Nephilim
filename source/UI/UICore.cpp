#include <Nephilim/UI/UICore.h>

NEPHILIM_NS_BEGIN

UICore::UICore()
: transformPointerCoordinates(false)
, m_defaultFont(NULL)
, defaultPositionFlags(0)
, defaultSizeFlags(0)
, content(NULL)
{
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
}
NEPHILIM_NS_END