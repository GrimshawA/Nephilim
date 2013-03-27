#ifndef PARABOLA_FILEINTERFACE_H
#define PARABOLA_FILEINTERFACE_H

#include "Platform.h"
#include "Strings.h"
#include "Signals.h"
#include "IODevice.h"

PARABOLA_NAMESPACE_BEGIN

class ScopedFile;

class PARABOLA_API FileInterface{
public:
	
	/// Get an open handle to an asset in the underlying filesystem
	/// Returns NULL if the file was innacessible or not found
	/// By default ReadOnly is passed as the open mode but please notice that in some cases only that flag is allowed
	/// For example, when loading an asset packaged in an Android APK
	/// Please ensure you delete the handle when you are done
	static bool getAssetFile(ScopedFile* file, const String &path, bool binaryMode = true);

	/// Copies the contents of sourceFile to destinationFile
	/// \return true or false whether the operation was successfully made
	static bool copy(const String &sourceFile, const String &destinationFile);

	/// Called whenever a file was requested for opening
	/// Possible use is to download the file to a cache before using it
	static sigc::signal<void, const String &> onFileRequest;

	/// The root for file access, empty by default, so the executable directory is used
	static String m_root;
};

PARABOLA_NAMESPACE_END
#endif