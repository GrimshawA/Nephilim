#ifndef PARABOLA_STRINGSTREAM_H
#define PARABOLA_STRINGSTREAM_H

#include "Platform.h"
//#include "FileStream.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN
	/**
		\ingroup Foundation
		\class StringStream
		\brief Stream to parse content from a String object
	*/
/*	class PARABOLA_API StringStream: public DataStream{
	public:
		/// Creates a StringStream pointing to nowhere
		StringStream();
		/// Creates a StringStream to parse in
		StringStream(String &in);
		/// Destructs the Stream
		~StringStream();

		/// Tells if the stream has reached the end of the String
		/// In the absence of a string, returns true
		bool atEnd();

		/// Skip characters while they match c
		void skipWhile(char c);

		/// Reads one character
		char readChar();

		/// Travels by ByteCount in the stream. Negative values allowed.
		/// It clamps between 0 and the length() of the function
		void seekOffset(int byteCount);

		/// Reads all the chars left
		String readAll();

		/// Keeps reading characters until stop is found
		String readUntil(char stop);
		
		/// Reads a block of text between begin and end characters
		/// Nested blocks with the same characters will be accounted for.
		String readBlock(char begin, char end);

		/// Reads a alphabetic-only composed string, skips all characters until the first alpha char
		String readWord();

	private:
		int pos;
		String *str;
	};*/

PARABOLA_NAMESPACE_END
#endif