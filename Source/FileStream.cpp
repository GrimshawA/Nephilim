//#include "Nephilim/FileStream.h"
//#include <stdio.h>
//#include <cstdlib>

//PARABOLA_NAMESPACE_BEGIN

//FILE* fopen_alt(const String &str, IODevice::OpenModes mode){
	/*using namespace StreamMode;
	String res;
	switch(mode){
		case 0: res = "rb";break;
		case 1: res = "wb";break;
		case 2: res = "ab";break;
		case 3: res = "r+b";break;
		case 4: res = "w+b";break;
		case 5: res = "a+b";break;
			// Half binary and half text
		case 6: res = "r";break;
		case 7: res = "w";break;
		case 8: res = "a";break;
		case 9: res = "r+";break;
		case 10: res = "w+";break;
		case 11: res = "a+";break;
	}

	return fopen(str.c_str(), res.c_str());*///return NULL;
//};
/*
FileStream::FileStream(){
	file_handle = NULL;
	open_mode = -1;
};

/// Creates the stream from an already open FILE*
FileStream::FileStream(FILE* filePointer){
	file_handle = filePointer;
	open_mode = StreamMode::Unknown;
};

FileStream::FileStream(String fileName, unsigned int openMode){
	file_handle = NULL;

	open(fileName, (IODevice::OpenModes)openMode);
};

/// Destroys the stream and releases its handle if any exists.
FileStream::~FileStream(){
	close();
};

/// Allows if(stream) tests for validity
FileStream::operator bool() const{
	return (const_cast<FileStream&>(*this).handle() != NULL);
};
/// Allows if(!stream) tests for validity
bool FileStream::operator !(){
	return (handle() == NULL);
};

/// Checks if the file was successfully opened
bool FileStream::valid(){
	if(file_handle)return true;
	else return false;
};

/// Copies the contents of the file to destination file
/// \return true or false depending on if the copy happened successfully.
bool FileStream::copy(const String &path){
	FileStream in(path, StreamMode::ReadOnly);
	if(!in.valid() || !valid())return false;

	const unsigned int buffer_size = sizeof(char)*1024*5;
	char buffer[buffer_size];
	Int64 bytes_read;
	do{
		bytes_read = in.read(&buffer[0], buffer_size);
		write(&buffer[0], bytes_read);
	}while(bytes_read >= buffer_size);
	return true;
};

/// Copies the contents of sourceFile to destinationFile
/// \return true or false whether the operation was successfully made
bool FileStream::copy(const String &sourceFile, const String &destinationFile){
	FileStream in(sourceFile, StreamMode::ReadOnly);
	FileStream out(destinationFile, StreamMode::WriteOnly);
	if(!in.valid() || !out.valid() )return false;

	const unsigned int buffer_size = sizeof(char)*1024*5;
	char buffer[buffer_size];
	Int64 bytes_read;
	do{
		bytes_read = in.read(&buffer[0], buffer_size);
		out.write(&buffer[0], bytes_read);
	}while(bytes_read >= buffer_size);
	return true;
};

/// Returns the handle to the file the stream is pointing to. Compatible with C File API functions.
/// \return NULL if no file is open.
FILE* FileStream::handle(){
	return file_handle;
};

/// Returns the file name of the currently opened file. 
/// \return empty string if no file is open.
String FileStream::fileName(){
	return this->file_name;
};

bool FileStream::atEnd(){
	if(feof(handle()) != 0)return true;
	else return false;
};

void FileStream::setFileName(String fileName){
	if(valid()){
		close();
		open(fileName, openMode());
	}
	
	file_name = file_name;
};

IODevice::OpenModes FileStream::openMode(){
	return (IODevice::OpenModes)open_mode;
};

void FileStream::setOpenMode(IODevice::OpenModes mode){
	if(valid()){
		close();

		open_mode = mode;

		open();
	}
	else
		open_mode = mode;
};


/// Attempts to load a file, assuming that the Stream open mode and the filename were already passed.
bool FileStream::open(){
	if(fileName().length() > 0 && openMode() != -1){
		close();

		file_handle = fopen_alt(fileName(), openMode());

		if(valid())return true;
		else return false;
	}
	else return false; //no parameters to open it.
};

/// Attempts to load the file specified with in the mode specified
bool FileStream::open(String fileName, IODevice::OpenModes openMode){
	if(valid())close();

	setFileName(fileName);
	setOpenMode(openMode);

	file_handle = fopen_alt(fileName, openMode);

	return file_handle ? true : false;
};

/// Becomes a valid stream if the raw FILE* passed in is valid.
bool FileStream::open(FILE* fp){
	setOpenMode(IODevice::BinaryRead);
	file_handle = fp;
	return valid();
};

/// Closes the file handle
void FileStream::close(){
	if(valid()){
		fclose(file_handle);
		file_handle = NULL;
		setOpenMode(IODevice::BinaryRead);
	}	
};

/// Deletes the file from the file system.
bool FileStream::remove(String fileName){
	if(::remove(fileName.c_str()) > 0)
		return false;
	else return true;
};

/// Renames the file to a new name
bool FileStream::rename(String name){
	close();
	if(::rename(fileName().c_str(), name.c_str()) > 0)
		return false;
	else return true;
};

/// Flushes the stream buffer
void FileStream::flush(){
	if(valid())fflush(handle());
};

/// Error checking. Returns an integer value different from zero if an error occurred.
/// An example of an error could be writing to a read-only file.
int FileStream::error(){
	return ferror(handle());
};

/// Writes data to the file
/// \return the actual amount of bytes written
Int64 FileStream::write(const char *data, Int64 byte_len){
	return fwrite(data, sizeof(char), (size_t)byte_len, handle());
};

/// Reads data from the file
Int64 FileStream::read(char* data, Int64 byte_len){
	return fread(data, sizeof(char), (size_t)byte_len, handle());
};

/// Travels to desired position
bool FileStream::seek(Int64 position){
	if(fseek(handle(), (long)position, SEEK_SET) != 0 )return false;
	else return true;
};

bool FileStream::seekOffset(Int64 position){
	if(fseek(handle(), std::min<long>((long)position, 0), SEEK_CUR) != 0 )return false;
	else return true;
};

/// Tells the position of access the stream is currently at, relative to the beginning of the file.
Int64 FileStream::currentPosition(){
	return ftell(handle());
};

/// Returns the size in bytes of the file
Int64 FileStream::size(){
	Int64 were = currentPosition();
	fseek(handle(), 0, SEEK_END);
	Int64 result = currentPosition();
	seek(were);
	return result;
};

/// Static variant of Int64 size()
Int64 FileStream::size(const String &fileName){
	FileStream in(fileName.c_str(), StreamMode::ReadOnly);

	if(in.valid()){
		return in.size();
	}
	else
		return -1;
};

bool FileStream::exists(String fileName){
	return FileStream(fileName, StreamMode::ReadOnly).valid();
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const String &value){
	*this << (Int64)value.size();
	fwrite(value.c_str(), sizeof(char), value.size(), handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const char* value){
	size_t t = strlen(value);
	*this << t;
	fwrite(value, sizeof(char), t, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const bool value){
	fwrite(&value, sizeof(bool), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const float value){
	fwrite(&value, sizeof(float), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const double value){
	fwrite(&value, sizeof(double), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Int64 value){
	fwrite(&value, sizeof(Int64), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Uint64 value){
	fwrite(&value, sizeof(Uint64), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Int32 value){
	fwrite(&value, sizeof(Int32), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Uint32 value){
	fwrite(&value, sizeof(Uint32), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Int16 value){
	fwrite(&value, sizeof(Int16), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Uint16 value){
	fwrite(&value, sizeof(Uint16), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Int8 value){
	fwrite(&value, sizeof(Int8), 1, handle());
	return *this;
};

/// Overloads of operator<< for basic types.
FileStream& FileStream::operator<<(const Uint8 value){
	fwrite(&value, sizeof(Uint8), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(String &value){
	Int64 s;
	*this >> s;
	char *buffer = new char[s];
	size_t readb = fread(buffer, sizeof(char), s, handle());
	if(readb == s)
		value = String(buffer, s);
	delete[] buffer;
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(char* value){
	size_t t;
	*this >> t;
	fread(value, sizeof(char), t, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(bool &value){
	fread(&value, sizeof(bool), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(float &value){
	fread(&value, sizeof(float), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(double &value){
	fread(&value, sizeof(double), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Int64 &value){
	fread(&value, sizeof(Int64), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Uint64 &value){
	fread(&value, sizeof(Uint64), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Int32 &value){
	fread(&value, sizeof(Int32), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Uint32 &value){
	fread(&value, sizeof(Uint32), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Int16 &value){
	fread(&value, sizeof(Int16), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Uint16 &value){
	fread(&value, sizeof(Uint16), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Int8 &value){
	fread(&value, sizeof(Int8), 1, handle());
	return *this;
};

/// Overloads of operator>> for basic types.
FileStream& FileStream::operator>>(Uint8 &value){
	fread(&value, sizeof(Uint8), 1, handle());
	return *this;
};*/

//PARABOLA_NAMESPACE_END
