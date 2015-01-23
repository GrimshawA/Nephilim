#ifndef Clipboard_h__
#define Clipboard_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class Clipboard
	\brief Copy and paste functionality, internal and external
*/
class NEPHILIM_API Clipboard
{
public:
	
	/// Returns the current contents of the clipboard
	static String getClipboardText();

};

NEPHILIM_NS_END

#endif // Clipboard_h__
