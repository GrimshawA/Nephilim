#include <Nephilim/Foundation/NativeFileDialog.h>

#include <cstring>

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

NEPHILIM_NS_BEGIN

FileDialog::FileDialog()
: filter("")
, initialPath("K:\\")
{

}


String FileDialog::load()
{
#ifdef NEPHILIM_WINDOWS
	char Filestring[256];
	String returnstring;

	OPENFILENAMEA opf;
	opf.hwndOwner = NULL;
	opf.lpstrFilter = filter;
	opf.lpstrCustomFilter = 0;
	opf.nMaxCustFilter = 0L;
	opf.nFilterIndex = 1L;
	opf.lpstrFile = Filestring;
	opf.lpstrFile[0] = '\0';
	opf.nMaxFile = 256;
	opf.lpstrFileTitle = 0;
	opf.nMaxFileTitle=50;
	opf.lpstrInitialDir = initialPath.c_str();
	opf.lpstrTitle = title.c_str();
	opf.nFileOffset = 0;
	opf.nFileExtension = 0;
	opf.lpstrDefExt = "*.*";
	opf.lpfnHook = NULL;
	opf.lCustData = 0;
	opf.Flags = (OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR) & ~OFN_ALLOWMULTISELECT ;
	opf.lStructSize = sizeof(OPENFILENAME);

	if(GetOpenFileNameA(&opf))
	{
		std::string s = static_cast<std::string>(opf.lpstrFile);
		returnstring.assign(s.begin(), s.end());
	}

	return returnstring;
#endif
	return "";
}

String FileDialog::save()
{
#ifdef NEPHILIM_WINDOWS

	OPENFILENAMEA ofn;
	String result;
	
	char saveFileName[MAX_PATH] = "";

	ZeroMemory( &ofn, sizeof( ofn ) );

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = filter;
//	ofn.lpstrFilter = "Script file (*.as)\0*.as\0";
	ofn.lpstrFile = saveFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "*.*";
	ofn.Flags  = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	ofn.lpstrTitle = title.c_str();
	

	if(GetSaveFileNameA(&ofn)){	
		std::string s = static_cast<std::string>(ofn.lpstrFile);
		result.assign(s.begin(), s.end());
	}
	
	return result;
#endif
	return "";
}

NEPHILIM_NS_END