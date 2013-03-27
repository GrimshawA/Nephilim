#include <Nephilim/Clipboard.h>

#include <stdio.h>

#ifdef PARABOLA_WINDOWS
#include <windows.h>
#endif

PARABOLA_NAMESPACE_BEGIN

/// Returns the current contents of the clipboard
String Clipboard::getClipboardText(){
#ifdef PARABOLA_WINDOWS
	HANDLE clip;
	if (OpenClipboard(NULL)) 
		clip = GetClipboardData(CF_TEXT);
	printf("%s\n",clip);
#endif
	return "";
}

PARABOLA_NAMESPACE_END