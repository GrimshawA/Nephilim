#ifndef PARABOLA_TEXTFILESTREAM_H
#define PARABOLA_TEXTFILESTREAM_H

#include "Platform.h"
#include "FileStream.h"

PARABOLA_NAMESPACE_BEGIN

	/**
		\ingroup Foundation
		\class TextFileStream
		\brief A special kind of FileStream to deal with text files.

		This class provides methods to make it easy to load/write text files. 
		It is naturally able to parse files, even under different "virtual languages" you can create.
	*/
	class PARABOLA_API TextFileStream: public FileStream{
	public:
		/// Creates a stream that points to nowhere
		TextFileStream();
		/// Creates a stream pointing to the device specified, if possible.
		TextFileStream(FILE* Handle);
		/// Creates a stream from a file specified, under the chosen mode 
		TextFileStream(String FileName, unsigned int OpenMode);

		/// Destroys the handle to the file, if exists.
		/// Guarantees the release of the object when going out of scope.
		~TextFileStream();


		/// Standard stream - stdout. 
		/// Effectively, writing data to this stream will write it to the console or where the output is being redirected.
		static TextFileStream Out;
		/// Standard stream - stdin
		/// Reading data from this stream will cause it to be read from the console or where the input is coming from.
		static TextFileStream In;
		/// Standard stream - stderr
		/// Following the other standard streams, should work as stderr usually works.
		static TextFileStream Err;

		/// Set the delimiter for read functions
		/// By default, the delimiter is space ' '
		/// In effect, when using a function such as nextString(), the resulting string will be a segment found between the delimiter.
		void setDelimiter(char c);
		/// Set the delimiter for read functions
		/// By default, the delimiter is space ' '
		/// In effect, when using a function such as nextString(), the resulting string will be a segment found between the delimiter.
		void setDelimiter(const String &s);

		// Java-style parsing

		/// Advances in the file and attempts to find a valid string
		/// Whatever result, the reading position in the file is kept unchanged.
		bool hasNext();
		/// Returns a string that matches the next segment of characters delimited by the chosen delimiter() .
		/// It is advised that this function is called only after checking there is a result, using hasNext().
		String nextString();

		/// Checks if there is an int to read next
		bool hasNextInt();

		/// Returns the next integer value in the file.
		int nextInt();

		/// Checks if there is a float to read any further in the file.
		bool hasNextFloat();

		/// Returns the next float found in the file.
		float nextFloat();

		/// Reads one character from the stream. It will be EOF if atEnd() is true.
		char readChar();

		/// Ignores the rest of the line content.
		/// In effect, it will skip all characters until \n (line-break) is found.
		void skipLine();

		/// Keeps advancing characters while they match c
		void skipChar(char c);

		/// Skips all characters until c is found.
		/// After calling this function, readChar() will return the character after c
		void skipUntil(char c);

		/// Skips all whitespace
		void skipWhitespace();

		/// Reads the whole line from the stream
		String getLine(); 

		/// Travels to the nearby occurrence of c
		/// After you call this function, readChar() will return c
		/// Returns false if c did not occur anymore.
		bool findChar(char c);

		/// Builds a string by reading char-by-char until a undesirable char is found.
		/// By default, readWord() will return a contiguous text with only letters.
		/// For now, you can pass arguments to make the function allow numbers and _ in the string.
		String readWord(bool acceptNumbers = false, bool acceptUnderscore = false);
		
		/// Returns the next segment of text that is between beginChar and endChar
		/// For that, it finds the next occurrence of beginChar and starts building the string until it finds endChar.
		/// If there are other nested blocks within the one that is being built, they are copied too instead of confusing the function.
		String readBlock(char beginChar, char endChar);

		/// Overloads of operator<< for basic types.
		FileStream& operator<<(const String &value);

		/// Overloads of operator>> for basic types.
		FileStream& operator>>(String &value);

	private:
		String delimiter;
	};

PARABOLA_NAMESPACE_END
#endif