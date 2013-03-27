#ifndef PARABOLA_SCOPEDFILESTREAM_H
#define PARABOLA_SCOPEDFILESTREAM_H

#include "Platform.h"
#include "Strings.h"
#include "IODevice.h"
#include "ReferenceCountable.h"
#include <stdio.h>

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Foundation
	\class ScopedFile
	\brief File interaction class. Use this instead of FILE* for true cross-platform support

	The main feature of ScopedFile is to support seamlessly reading from entire files and specified regions, like an APK asset, or a file within a package.

*/
class PARABOLA_API ScopedFile : public IODevice, public RefCountable{
public:
	/// Constructs an uninitialized stream
	ScopedFile();
	/// Constructs a stream that takes over the whole file
	ScopedFile(const String &path, IODevice::OpenModes accessMode);
	/// Constructs a stream from already open file handle, restricted to a portion of it
	ScopedFile(FILE* fileHandle, Int64 startOffset, Int64 length);

	/// Cleanup
	virtual ~ScopedFile();

	/// Opens this file from an already open handle
	/// startOffset defines where does the allowed region start, for the whole file it is 0
	/// length is the size of the region to read, it will be equal to the fileSize for reading without boundaries.
	/// If you don't know the length when calling this function, pass -1 if you want the whole file.
	bool open(FILE* fileHandle, Int64 startOffset, Int64 length);

	/// Check if the file is open and ready
	bool isReady();

	/// Checks if the file has reached its end
	bool atEnd();

	/// Read the next character available - uses fgetc and assumes an open mode for text
	char getChar();

	/// Read a line
	String getLine();

	/// Retrive the file handle
	FILE* getHandle();

	/// Check if the stream can be read from
	/// Used normally to check if the opening was sucessfull
	bool canRead();

	/// Seeks to the desired position in the file, clamped within the access restriction limits, if any.
	/// Please notice that when you try to seek the beggining, its the beggining of the allowed section you get.
	/// Returns true if the operation was sucessfull
	bool seek(Int64 offset, int origin = SEEK_SET);

	/// Reads raw data from the stream with size len, stored in the buffer, it protects the reading of protected sections
	/// Returns the amount of bytes read
	Int64 read(char* buffer, Int64 len);

	/// Tells the current position, relative to the allowed offset
	Int64 tell();

	/// Get the total size of the file (or region)
	Int64 getSize();

	/// Write data into the file
	Int64 write(const char* buffer, Int64 length);

	/// Allows to check for a file size
	static Int64 getFileSize(String path);

private:
	Int64 m_offset;
	Int64 m_length;
	Int64 m_fileSize;
	FILE* m_handle;
};

class ASEngine;
bool registerScopedFile(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif