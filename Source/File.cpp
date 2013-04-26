#include <Nephilim/File.h>
#include <Nephilim/Logger.h>

#include <Nephilim/ASEngine.h>
#include "AS/aswrappedcall.h"

#include <cmath>
#include <stdlib.h>

NEPHILIM_NS_BEGIN

File::File()
: m_creator(false)
, m_handle(NULL)
, m_offset(0)
, m_length(0)
, m_fileSize(0)
{
}

/// Constructs a stream that takes over the whole file
File::File(const String &path, IODevice::OpenModes accessMode)
: m_handle(NULL)
, m_length(0)
, m_offset(0)
{
	String mode;
	switch(accessMode){
		case IODevice::BinaryRead: mode = "rb";break;
		case IODevice::BinaryWrite: mode = "wb";break;
		case IODevice::TextRead: mode = "r";break;
		case IODevice::TextWrite: mode = "w";break;
	}
#ifdef NEPHILIM_ANDROID
	if(path.length() > 0 && path[0] != '/')
	{
		// Asset
		AndroidInterface::AssetFile asset = AndroidInterface::getAsset(path);
		if(asset.success)
		{
			m_handle = fdopen(asset.fd, mode.c_str());
			m_offset = asset.offset;
			m_length = asset.length;
			if(m_handle) 
				fseek(m_handle, m_offset, SEEK_SET);
		}
	}
	else m_handle = fopen(path.c_str(), mode.c_str());
#else
	// Standard opening
	m_handle = fopen(path.c_str(), mode.c_str());
#endif
	
	if(m_handle && m_length == 0){
		fseek(m_handle, 0, SEEK_END);
		m_length = m_fileSize = ftell(m_handle);
		fseek(m_handle, 0, SEEK_SET);
	}
};

/// Constructs a stream from already open file handle, restricted to a portion of it
File::File(FILE* fileHandle, Int64 startOffset, Int64 length)
: m_creator(false)
{
	m_handle = fileHandle;
	m_offset = startOffset;
	m_length = length;

	fseek(m_handle, 0 , SEEK_END);
	m_fileSize = ftell(m_handle);
	fseek(m_handle, m_offset, SEEK_SET);

	String found = "Found the asset on offset " + String::number((long int)m_offset) + " with len " + String::number((long int)m_length);
	TESTLOG(found.c_str())
};

File::operator bool()
{
	return m_handle != NULL;
}

/// Read a line
String File::getLine()
{
	String s;
	char c = 0;
	while(!atEnd() && c != '\n')
	{
		s += (c = getChar());
	}
	return s;
};

/// Cleanup
File::~File(){
	fclose(m_handle);
}

/// Write data into the file
Int64 File::write(const char* buffer, Int64 length) const{
	return fwrite(buffer, sizeof(char), length, m_handle);
};

/// Opens this file from an already open handle
/// startOffset defines where does the allowed region start, for the whole file it is 0
/// length is the size of the region to read, it will be equal to the fileSize for reading without boundaries.
/// If you don't know the length when calling this function, pass -1 if you want the whole file.
bool File::open(FILE* fileHandle, Int64 startOffset, Int64 length){
	m_handle = fileHandle;
	m_offset = startOffset;
	m_length = length;
	m_fileSize = m_length;


	/// Case for whole file
	if(length == -1){
		fseek(m_handle, 0 , SEEK_END);
		m_fileSize = ftell(m_handle);
		fseek(m_handle, m_offset, SEEK_SET);

		m_length = m_fileSize;
	}
	else{
		m_length = m_fileSize = length;
		fseek(m_handle, m_offset, SEEK_SET);
	}

	return true;
};

/// Check if the file is open and ready
bool File::isReady(){
	return (m_handle != NULL);
};

/// Checks if the file has reached its end
bool File::atEnd(){
	return (tell() >= m_fileSize);
};

/// Read the next character available - uses fgetc and assumes an open mode for text
char File::getChar(){	
	return fgetc(m_handle);
};

/// Retrive the file handle
FILE* File::getHandle(){
	return m_handle;
};



/// Check if the stream can be read from
/// Used normally to check if the opening was sucessfull
bool File::canRead(){
	return (m_handle != NULL);
};

/// Seeks to the desired position in the file, clamped within the access restriction limits, if any.
/// Please notice that when you try to seek the beggining, its the beggining of the allowed section you get.
/// Returns true if the operation was sucessfull
bool File::seek(Int64 offset, int origin){
	if(origin == SEEK_SET){
		//seeking from the beggining
		offset += m_offset; //always relative to the offset
		if(offset > m_offset + m_length) return false; //cant seek out of bounds
		else{
			return (fseek(m_handle, offset, origin) == 0);
		}
	}
	else if(origin == SEEK_CUR){
		Int64 currentPos = tell();/// TODO
		//TESTLOG("Curr SEEK IS USED")
		return (fseek(m_handle, offset, origin) == 0);
	}
	else if(origin == SEEK_END){
		if(offset > 0)return false; //cant accept positive values

		else return (fseek(m_handle, m_offset + m_length + offset, SEEK_SET) == 0);
	}
	else return false;
};

/// Get the total size of the file (or region)
Int64 File::getSize(){
	return m_length;
};

/// Reads raw data from the stream with size len, stored in the buffer, it protects the reading of protected sections
/// Returns the amount of bytes read
Int64 File::read(char* buffer, Int64 len) const{
	Int64 curPos = tell();
	if(curPos >= m_length) return 0;

	if(len > m_length - curPos) len = m_length - curPos; // if trying to read more than whats left, clamp

	return (Int64)fread(buffer, sizeof(char), len, m_handle);
};

/// Tells the current position, relative to the allowed offset
Int64 File::tell() const{
	Int64 curr = ftell(m_handle);
	return curr - m_offset;
};

/// Allows to check for a file size
Int64 getFileSize(String path){
	return 0; // TODO
};

namespace FileOps
{
	Int64 size(const String& src)
	{
		Int64 fileSize = 0;
		File in(src, IODevice::BinaryRead);
		if(in.isReady()) fileSize = in.getSize();
		return fileSize;
	}

	void copy(const File& src, const File& dst)
	{
		Int64 t = 0;
		char* buffer = new char[100];
		Int64 readBytes = 0;
		do
		{
			readBytes = src.read(buffer, 100);
			t+= readBytes;
			dst.write(buffer, readBytes);
		} while (readBytes > 0);
		cout<<"FILE OPERATION COPY: " << t << endl;
		delete [] buffer;
	}
}

NEPHILIM_NS_END
