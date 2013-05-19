#include "Nephilim/FileSystem.h"

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#include <Shlobj.h>
#include <CommDlg.h>
#undef SetCurrentDirectory
#elif defined NEPHILIM_ANDROID
#include "Nephilim/AndroidInterface.h"
#include "Nephilim/Logger.h"
#endif

NEPHILIM_NS_BEGIN
	String FileSystem::myCurrentDirectory;

#ifdef NEPHILIM_WINDOWS
	std::wstring wide_string_from_string(std::string str){
		return std::wstring(str.begin(), str.end());
	}
#endif

/// Load a dialog
String FileSystem::loadFileDialog(){
#ifdef NEPHILIM_WINDOWS
		char Filestring[256];
		String returnstring;
		
		OPENFILENAMEA opf;
		opf.hwndOwner = NULL;
		opf.lpstrFilter = "";
		opf.lpstrCustomFilter = 0;
		opf.nMaxCustFilter = 0L;
		opf.nFilterIndex = 1L;
		opf.lpstrFile = Filestring;
		opf.lpstrFile[0] = '\0';
		opf.nMaxFile = 256;
		opf.lpstrFileTitle = 0;
		opf.nMaxFileTitle=50;
		opf.lpstrInitialDir = "K:\\";
		opf.lpstrTitle = "Nephilim";
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
#else
	return "";
#endif
	return "";
};

/// Testing \todo make
String FileSystem::saveFileDialog(){
#ifdef NEPHILIM_WINDOWS
	OPENFILENAME ofn;
	String result;
	/*
	wchar_t saveFileName[MAX_PATH] = L"";

	ZeroMemory( &ofn, sizeof( ofn ) );

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Script file (*.as)\0*.as\0";
	ofn.lpstrFile = saveFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = L"as";
	ofn.Flags  = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	ofn.lpstrTitle = L"Save File";
	

	if(GetSaveFileName(&ofn)){	
		std::wstring s = static_cast<std::wstring>(ofn.lpstrFile);
		result.assign(s.begin(), s.end());
	}
	*/
	return result;
	//	wcscpy(file,saveFileName);
#else
	return "";
#endif
	return "";
};

String FileSystem::getDocumentsDirectory(){
	String ActualStorageDirectory;
#ifdef NEPHILIM_WINDOWS
	ActualStorageDirectory.resize(1024);

	if(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, &ActualStorageDirectory[0]) < 0)
	{
		ActualStorageDirectory.clear();
	}
	else
	{
		ActualStorageDirectory.resize(strlen(ActualStorageDirectory.c_str()));
	};
#endif

	ActualStorageDirectory.replaceCharacter('\\', '/');
	return ActualStorageDirectory;

};


/// Get the path of the executable - could be similar to C:/Games/ or /home/games/
String FileSystem::getExecutableDirectory(){
	String path;
#ifdef NEPHILIM_WINDOWS
	/*LPSTR lpStr = new char[2048];
	GetModuleFileNameA(NULL,lpStr,2048 );
	path = lpStr;
	delete lpStr;

	path.removeUntilReverse('\\');
	path.replaceCharacter('\\', '/');

	path += "/";*/
#endif

	return path;
};

	StringList FileSystem::scanDirectory(const String &Directory, const String &Extension, bool Recursive){
		//std::vector<String> Files;

		StringList Files;
		{
		#ifdef NEPHILIM_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = Directory + String("\\*.") + Extension;
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return Files;

			String FileName(FileData.cFileName);

			if(FileName[0] != '.')
			{
				if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if(Recursive)
					{
						StringList t(scanDirectory(Directory + String("/") +
							String(FileData.cFileName), Extension, Recursive));

						Files.insert(Files.end(), t.begin(), t.end());
					};
				}
				else
				{
					String FileName(FileData.cFileName);
					Files.push_back(Directory + String("/") + FileName);
				};
			};

			while(FindNextFileA(hFindHandle, &FileData))
			{
				FileName = FileData.cFileName;

				if(FileName[0] != '.')
				{
					if(Recursive)
					{
						StringList t(scanDirectory(Directory + String("/") +
							String(FileData.cFileName), Extension, Recursive));

						Files.insert(Files.end(), t.begin(), t.end());
					}

					Files.insert(Files.end(), Directory + String("/") + FileName);

				}
				else
				{
					//Files.insert(Files.end(), Directory + String("/") + FileName);
				};
			};

			FindClose(hFindHandle);
		#elif defined(PARABOLA_PLATFORM_LINUX) || defined(PARABOLA_PLATFORM_MAC)///////////////////////MAC|LINUX
			DIR *Root = opendir (Directory);

			if(Root == nullptr)
			{
				return Files;
			}

			dirent *Entry = readdir(Root);

			while(Entry != nullptr)
			{
				String FileName(Entry->d_name);

				if(FileName[0] != '.')
				{
					if(Entry->d_type == DT_DIR)
					{
						if(Recursive)
						{
							std::vector<String> t(scanDirectory(Directory + String("/") +
								String(FileData.cFileName), Extension, Recursive));

							Files.insert(Files.end(), t.begin(), t.end());
						};
					}
					else if(Entry->d_type == DT_REG)
					{
						Files.push_back(Directory + String("/") + FileName);
					};
				};

				Entry = readdir(Root);
			}

			closedir(Root);
	#elif defined PARABOLA_ANDROID
		Files = AndroidInterface::getAssetList(Directory);


	#endif
		}

		return Files;
	}

	
	bool FileSystem::isDirectory(String Directory){
		#ifdef NEPHILIM_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = Directory;
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return false;

			String FileName(FileData.cFileName);
			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				return true;
			else
				return false;

		#else

		#endif
	};


	bool FileSystem::isFile(String fileName){
		#ifdef NEPHILIM_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = fileName;
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return false;

			String FileName(FileData.cFileName);
			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
				return true;
			else
				return false;

		#else

		#endif
	}


	StringList FileSystem::directoryList(String Where, bool KeepRelativePath){
		StringList Files;
		{
		#ifdef NEPHILIM_WINDOWS ////////////////////////////////////////////////////WINDOWS CONFIG
			String Query = Where + String("\\*");
			WIN32_FIND_DATAA FileData;
			HANDLE hFindHandle = INVALID_HANDLE_VALUE;
			hFindHandle = FindFirstFileA(Query.c_str(), &FileData);

			if(hFindHandle == INVALID_HANDLE_VALUE)
				return Files;

			String FileName(FileData.cFileName);

			if(FileName[0] != '.' && FileName != "..")
			{
				if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					String FileName(FileData.cFileName);
					if(KeepRelativePath)
						Files.push_back(Where + String("/") + FileName);
					else
						Files.push_back(FileData.cFileName);

				}
				
			};

			while(FindNextFileA(hFindHandle, &FileData))
			{
				FileName = FileData.cFileName;

				if(FileName[0] != '.' && FileName != "..")
				{
					if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						String FileName(FileData.cFileName);
						if(KeepRelativePath)
							Files.push_back(Where + String("/") + FileName);
						else
							Files.push_back(FileData.cFileName);
					}
					
				};
			};

			FindClose(hFindHandle);
		#elif defined(PARABOLA_PLATFORM_LINUX) || defined(PARABOLA_PLATFORM_MAC)///////////////////////MAC|LINUX
			DIR *Root = opendir (Directory);

			if(Root == nullptr)
			{
				return Files;
			}

			dirent *Entry = readdir(Root);

			while(Entry != nullptr)
			{
				String FileName(Entry->d_name);

				if(FileName[0] != '.')
				{
					if(Entry->d_type == DT_DIR)
					{
						if(Recursive)
						{
							std::vector<String> t(scanDirectory(Directory + String("/") +
								String(FileData.cFileName), Extension, Recursive));

							Files.insert(Files.end(), t.begin(), t.end());
						};
					}
					else if(Entry->d_type == DT_REG)
					{
						Files.push_back(Directory + String("/") + FileName);
					};
				};

				Entry = readdir(Root);
			}

			closedir(Root); 
#elif defined PARABOLA_ANDROID
			 


	#endif
		}

		return Files;
	};

bool FileSystem::makeDirectory(String Name)
{
#ifdef NEPHILIM_WINDOWS
		//if(!CreateDirectoryA((LPCWSTR)wide_string_from_string(Name).c_str(), LPSECURITY_ATTRIBUTES()))
		if(!CreateDirectoryA((LPCSTR)Name.c_str(), LPSECURITY_ATTRIBUTES()))
			return false;
#elif defined PARABOLA_ANDROID
		TESTLOG("makeDirectory\n");
		return AndroidInterface::createDirectory(Name);
#else
		//TESTLOG("makeDirectory NOT android\n");
		//_mkdir(Name.c_str());
	//	mkdir(Name.c_str(), 0770);
#endif
	return true;
}

	String FileSystem::currentDirectory(){
		return myCurrentDirectory;
	}


NEPHILIM_NS_END
