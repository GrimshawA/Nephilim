#ifndef NephilimFile_h__
#define NephilimFile_h__

#include <Nephilim/Platform.h>
#include "Strings.h"
#include "IODevice.h"

#include <stdio.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\class File
	\brief Provides file access functionality even for android packaged assets
*/
class NEPHILIM_API File : public IODevice
{
public:
	/// Constructs an uninitialized file
	File();

	/// Constructs a stream that takes over the whole file
	File(const String &path, IODevice::OpenModes accessMode = IODevice::BinaryRead);

	/// Constructs a stream from already open file handle, restricted to a portion of it
	File(FILE* fileHandle, Int64 startOffset, Int64 length);

	/// Cleanup
	virtual ~File();

	operator bool();

	/// Opens this file from an already open handle
	/// startOffset defines where does the allowed region start, for the whole file it is 0
	/// length is the size of the region to read, it will be equal to the fileSize for reading without boundaries.
	/// If you don't know the length when calling this function, pass -1 if you want the whole file.
	bool open(FILE* fileHandle, Int64 startOffset, Int64 length);

	/// This overload opens a file from the filesystem in the "r+" mode, reading and writing
	bool open(const String& filename);

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
	Int64 read(char* buffer, Int64 len) const;

	/// Tells the current position, relative to the allowed offset
	Int64 tell() const;

	/// Get the total size of the file (or region)
	Int64 getSize();

	/// Write data into the file
	Int64 write(const char* buffer, Int64 length) const;

	/// Allows to check for a file size
	static Int64 getFileSize(String path);

private:
	Int64 m_offset; ///< Beggining of the file, 0 or any other byte
	Int64 m_length; ///< The length that is available to read
	Int64 m_fileSize;
	FILE* m_handle;
	bool  m_creator; ///< Specifies whether this File instance is responsible for releasing the handle
};

namespace FileOps
{
	Int64 size(const String& src);
	void copy(const File& src, const File& dst);
}

NEPHILIM_NS_END
#endif // NephilimFile_h__