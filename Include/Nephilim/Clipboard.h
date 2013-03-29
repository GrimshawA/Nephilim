#ifndef Clipboard_h__
#define Clipboard_h__

#include "Platform.h"
#include "Strings.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\class Clipboard
	\brief Copy & Paste functionality 
*/
class NEPHILIM_API Clipboard{
public:
	
	/// Returns the current contents of the clipboard
	static String getClipboardText();

};

NEPHILIM_NS_END

#endif // Clipboard_h__
