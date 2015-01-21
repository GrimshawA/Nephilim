#include <Nephilim/Clipboard.h>

#include <stdio.h>

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

NEPHILIM_NS_BEGIN

/// Returns the current contents of the clipboard
String Clipboard::getClipboardText(){
#ifdef NEPHILIM_WINDOWS
	HANDLE clip = NULL;
	if (OpenClipboard(NULL)) 
		clip = GetClipboardData(CF_TEXT);
	printf("%s\n",clip);
#endif
	return "";
}

NEPHILIM_NS_END