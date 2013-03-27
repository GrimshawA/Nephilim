#ifndef PARABOLA_FILESTREAM_H
#define PARABOLA_FILESTREAM_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN
		/**
			\ingroup Foundation
			\class FileStream
			\brief Specialization of a Stream to deal with common files in the binary way.

			You can use this stream to interact with files in your computer's storage.
			It is implemented on top of C file support, and uses a RAII methodology
			to make sure all handles are released and therefore no file is locked more time than
			the scope of the FileStream object.

			It's usage is pretty simple and not very different from other implementations.

			You can create a file such as in
			\code
				FileStream file("myfile.txt", StreamMode::ReadOnly);
			\endcode
			which imeddiatly opens the file in the constructor. You can then check if it was opened sucessfully
			\code
				if(file.valid()){doSomething();}
				else error("Could not open the file!");
			\endcode

			It implements operator << for common types, which write them directly to the stream,
			and the operator >> for common types, which reads them from the stream.

			These operators >> and << are configured for binary files serialization specifically,
			that means even a String boundaries will be known if read in the right order.
		*/
		/*class PARABOLA_API FileStream{
		public:
			/// Creates an empty object
			FileStream();
			/// Creates the stream from an already open FILE*
			FileStream(FILE* filePointer);
			/// Creates the stream from a file name and a mode on how to open it.
			FileStream(String fileName, unsigned int openMode);
			/// Destroys the stream and releases its handle if any exists.
			~FileStream();

			/// Checks if the file was successfully opened
			bool valid();

			/// Copies the contents of the file to destination file
			/// \return true or false depending on if the copy happened successfully.
			bool copy(const String &path);

			/// Copies the contents of sourceFile to destinationFile
			/// \return true or false whether the operation was successfully made
			static bool copy(const String &sourceFile, const String &destinationFile);

			/// Returns the handle to the file the stream is pointing to. Compatible with C File API functions.
			/// \return NULL if no file is open.
			FILE* handle();

			/// Allows if(stream) tests for validity
			operator bool() const;
			/// Allows if(!stream) tests for validity
			bool operator !();

			/// Get the access mode currently in use
			/// Causes the stream to reset to the new mode if it was already open
			IODevice::OpenModes openMode();

			/// Checks if the file has reached the end
			bool atEnd();

			/// Returns the file name of the currently opened file. 
			/// \return empty string if no file is open.
			String fileName();

			/// Set the filename of the desired handled file
			/// Note that this function will not change a file's name in the storage disk.
			/// If no file is open, it simply sets the name in advance.
			/// If there is a file already open, calling this will cause this stream to change into a new file, under the same settings.
			void setFileName(String fileName);

			/// Sets the mode of file access
			void setOpenMode(IODevice::OpenModes mode);

			/// Attempts to load a file, assuming that the Stream open mode and the filename were already passed.
			bool open();
			/// Attempts to load the file specified with in the mode specified
			bool open(String fileName, IODevice::OpenModes openMode);
			/// Becomes a valid stream if the raw FILE* passed in is valid.
			bool open(FILE* fp);

			/// Closes the file handle
			void close();

			/// Deletes the file from the file system.
			static bool remove(String fileName);

			/// Renames the file to a new name
			bool rename(String name);

			/// Flushes the stream buffer
			void flush();

			/// Error checking. Returns an integer value different from zero if an error occurred.
			/// An example of an error could be writing to a read-only file.
			int error();

			/// Writes data to the file
			/// \return the actual amount of bytes written
			Int64 write(const char *data, Int64 byte_len);

			/// Reads data from the file
			Int64 read(char* data, Int64 byte_len);

			/// Travels to desired position
			bool seek(Int64 position);

			/// Travels position bytes relative to the currentPosition(). Negative offsets are allowed.
			bool seekOffset(Int64 position);

			/// Tells the position of access the stream is currently at, relative to the beginning of the file.
			Int64 currentPosition();

			/// Returns the size in bytes of the file
			Int64 size();

			/// Static variant of Int64 size()
			static Int64 size(const String &fileName);

			/// Checks if a file exists.
			static bool exists(String fileName);

			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const String &value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const char* value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const bool value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const float value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const double value);			
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Int64 value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Uint64 value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Int32 value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Uint32 value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Int16 value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Uint16 value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Int8 value);
			/// Overloads of operator<< for basic types.
			FileStream& operator<<(const Uint8 value);			
			
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(String &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(char* value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(bool &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(float &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(double &value);			
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Int64 &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Uint64 &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Int32 &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Uint32 &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Int16 &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Uint16 &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Int8 &value);
			/// Overloads of operator>> for basic types.
			FileStream& operator>>(Uint8 &value);			

		private:
			String file_name;
			FILE* file_handle;
			unsigned long open_mode;
		};*/

PARABOLA_NAMESPACE_END
#endif