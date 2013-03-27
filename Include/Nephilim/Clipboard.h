#ifndef Clipboard_h__
#define Clipboard_h__

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Foundation
	\class Clipboard
	\brief Copy & Paste functionality 
*/
class PARABOLA_API Clipboard{
public:
	
	/// Returns the current contents of the clipboard
	static String getClipboardText();

};

PARABOLA_NAMESPACE_END

#endif // Clipboard_h__
