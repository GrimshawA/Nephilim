#ifndef NephilimUI_ComboBox_h__
#define NephilimUI_ComboBox_h__

#include <Nephilim/UI/UIView.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class UIComboBox
	\brief Allows to choose between different options

	The combo box can be multi lined or single-lined, using left and right arrows to choose
	or the mouse.

	The multi-lined version spans a box with multiple choice.
*/
class NEPHILIM_API UIComboBox : public UIView
{
public:

	/// Either multi or single lined
	bool _multiLined;

public:

	/// Constructs a default. dataless combo box
	UIComboBox();
};

NEPHILIM_NS_END
#endif // NephilimUI_ComboBox_h__
