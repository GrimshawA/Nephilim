#ifndef NephilimFileDialog_h__
#define NephilimFileDialog_h__

#include "Platform.h"
#include "Strings.h"

NEPHILIM_NS_BEGIN

/**
	\class FileDialog
	\brief Quick and simple file dialog to load/save files
*/
class NEPHILIM_API FileDialog
{
public:
	FileDialog();

	String load();
	String save();

	String title;
	String initialPath;
	char* filter;

};

NEPHILIM_NS_END
#endif // FileDialog_h__
