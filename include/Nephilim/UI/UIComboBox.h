#ifndef NephilimUI_ComboBox_h__
#define NephilimUI_ComboBox_h__

#include <Nephilim/UI/Widget.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class UIComboBox
	\brief Allows to choose between different options

	The combo box can be multi lined or single-lined, using left and right arrows to choose
	or the mouse.

	The multi-lined version spans a box with multiple choice.
*/
class NEPHILIM_API UIComboBox : public Widget
{
public:

	/// Either multi or single lined
	bool _multiLined;

	/// List of entries in the combo box
	std::vector<String> entries;

public:

	/// Constructs a default. dataless combo box
	UIComboBox();

	/// Add a new entry to the list
	void addEntry(const String& label);
};

NEPHILIM_NS_END
#endif // NephilimUI_ComboBox_h__
