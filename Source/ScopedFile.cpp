#include <Nephilim/ScopedFile.h>
#include <Nephilim/Logger.h>

#include <Nephilim/ASEngine.h>
#include "AS/aswrappedcall.h"

#include <cmath>
#include <stdlib.h>

PARABOLA_NAMESPACE_BEGIN

bool registerScopedFile(ASEngine* engine)
{
	engine->getASEngine()->RegisterObjectType("File", sizeof(ScopedFile), asOBJ_REF);

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@ f()", WRAP_FN(genericFactory<ScopedFile>), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("File", asBEHAVE_ADDREF, "void f()", WRAP_MFN(ScopedFile, addReference), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectBehaviour("File", asBEHAVE_RELEASE, "void f()", WRAP_MFN(ScopedFile, removeReference), asCALL_GENERIC);
		
		engine->getASEngine()->RegisterObjectMethod("File", "bool good()", WRAP_MFN(ScopedFile, isReady), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("File", "bool atEnd()", WRAP_MFN(ScopedFile, atEnd), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("File", "string getLine()", WRAP_MFN(ScopedFile, getLine), asCALL_GENERIC);
	}
	else
	{
		engine->getASEngine()->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@ f()", asFUNCTION(genericFactory<ScopedFile>), asCALL_CDECL);
		engine->getASEngine()->RegisterObjectBehaviour("File", asBEHAVE_ADDREF, "void f()", asMETHOD(ScopedFile, addReference), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectBehaviour("File", asBEHAVE_RELEASE, "void f()", asMETHOD(ScopedFile, removeReference), asCALL_THISCALL);
	
		engine->getASEngine()->RegisterObjectMethod("File", "bool good()", asMETHOD(ScopedFile, isReady), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("File", "bool atEnd()", asMETHOD(ScopedFile, atEnd), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("File", "string getLine()", asMETHOD(ScopedFile, getLine), asCALL_THISCALL);

	}
	return true;
};

/// Constructs an uninitialized stream
ScopedFile::ScopedFile() : RefCountable(){
	m_handle = NULL;
	m_offset = -1;
	m_length = -1;
	m_fileSize = -1;
};

/// Constructs a stream that takes over the whole file
ScopedFile::ScopedFile(const String &path, IODevice::OpenModes accessMode) : RefCountable(){
	String mode;
	switch(accessMode){
		case IODevice::BinaryRead: mode = "rb";break;
		case IODevice::BinaryWrite: mode = "wb";break;
		case IODevice::TextRead: mode = "r";break;
		case IODevice::TextWrite: mode = "w";break;
	}
	m_handle = fopen(path.c_str(), mode.c_str());
	m_offset = 0;

	if(m_handle){
		fseek(m_handle, 0, SEEK_END);
		m_length = m_fileSize = ftell(m_handle);
		fseek(m_handle, 0, SEEK_SET);
	}	
};

/// Constructs a stream from already open file handle, restricted to a portion of it
ScopedFile::ScopedFile(FILE* fileHandle, Int64 startOffset, Int64 length) : RefCountable(){
	m_handle = fileHandle; 
	m_offset = startOffset;
	m_length = length;

	fseek(m_handle, 0 , SEEK_END);
	m_fileSize = ftell(m_handle);
	fseek(m_handle, m_offset, SEEK_SET);

	String found = "Found the asset on offset " + String::number((long int)m_offset) + " with len " + String::number((long int)m_length);
	TESTLOG(found.c_str())
};

/// Read a line
String ScopedFile::getLine()
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
ScopedFile::~ScopedFile(){
	if(m_handle)
		fclose(m_handle);
}

/// Write data into the file
Int64 ScopedFile::write(const char* buffer, Int64 length) {
	return fwrite(buffer, sizeof(char), length, m_handle);	
};

/// Opens this file from an already open handle
/// startOffset defines where does the allowed region start, for the whole file it is 0
/// length is the size of the region to read, it will be equal to the fileSize for reading without boundaries.
/// If you don't know the length when calling this function, pass -1 if you want the whole file.
bool ScopedFile::open(FILE* fileHandle, Int64 startOffset, Int64 length){
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
bool ScopedFile::isReady(){
	return (m_handle != NULL);
};

/// Checks if the file has reached its end
bool ScopedFile::atEnd(){
	return (tell() >= m_fileSize);
};

/// Read the next character available - uses fgetc and assumes an open mode for text
char ScopedFile::getChar(){
	if(!atEnd())
		return fgetc(m_handle);
	else return EOF;
};

/// Retrive the file handle
FILE* ScopedFile::getHandle(){
	return m_handle;
};



/// Check if the stream can be read from
/// Used normally to check if the opening was sucessfull
bool ScopedFile::canRead(){
	return (m_handle != NULL);
};

/// Seeks to the desired position in the file, clamped within the access restriction limits, if any.
/// Please notice that when you try to seek the beggining, its the beggining of the allowed section you get.
/// Returns true if the operation was sucessfull
bool ScopedFile::seek(Int64 offset, int origin){
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
Int64 ScopedFile::getSize(){
	return m_fileSize;
};

/// Reads raw data from the stream with size len, stored in the buffer, it protects the reading of protected sections
/// Returns the amount of bytes read
Int64 ScopedFile::read(char* buffer, Int64 len){
	Int64 curPos = tell();
	if(curPos >= m_length) return 0;

	if(len > m_length - curPos) len = m_length - curPos; // if trying to read more than whats left, clamp

	return (Int64)fread(buffer, sizeof(char), len, m_handle);
};

/// Tells the current position, relative to the allowed offset
Int64 ScopedFile::tell(){
	Int64 curr = ftell(m_handle);
	return curr - m_offset; 
};   

/// Allows to check for a file size
Int64 getFileSize(String path){
	return 0; // TODO
};
 
PARABOLA_NAMESPACE_END