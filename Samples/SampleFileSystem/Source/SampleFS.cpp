#include "SampleFS.h"

#include <Nephilim/File.h>
#include <Nephilim/TextStream.h>

#include <iostream>
#include <cassert>
using namespace std;

void SampleFS::onCreate()
{	
	// -- In Windows / Linux / Mac / IOS the File class operates directly on absolute paths with the FILE* facility
	// -- For android specifically, that is only possible for files in the sd card and you need the permission for it in the manifest
	// -- The android APK embeds your resources directly, under the assets directory. Those are incompatible to work with a normal FILE* out of the box,
	//    however, the File class automatically handles this. The files under the assets/ directory are packaged in some kind of zip archive, uncompressed.
	//    In that case, the File class knows how to access that zip at the right place, providing a protected access for that file's region only.
	//    !Note: All assets in the APK assets/ directory must have an additional extension .png, even if they are already png files.
	//    !This extension avoids compression of the files and also helps the File class to locate those files.
	//	  In android, all relative paths refer to the assets/ directory and all absolute paths refer to the external/userdata storage.

	// -- Because this class is naturally built to handle regions of files, it fits perfectly in handling both packaged and loose files.

	// By default the open mode is IODevice::BinaryRead
	File file1("a.txt");
	if(file1)
	{
		// It is this easy to get a line of text from the open file
		//cout << file1.getLine()<<endl;

		/*TextStream txt(file1);
		int number = txt.readInt();
		int number2 = txt.readInt();
		cout << "Reading an integer from line 2: " << number << " and another: " << number2 << endl;*/

		PRINTLOG("f", "Read line: %c\n", file1.getChar());
	}
	else cout << "Too bad. The file doesn't exist or is inoperable." << endl;
}
