#ifndef PARABOLA_TEXTFILESTREAM_H
#define PARABOLA_TEXTFILESTREAM_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

class IODevice; //forward decl

/**
	\ingroup Foundation
	\class TextStream
	\brief A stream that can read from IODevices with text parsing functions

	This class provides methods to make it easy to load/write text files. 
	It is naturally able to parse files, even under different "virtual languages" you can create.
*/
class PARABOLA_API TextStream{
public:
	/// An yet empty stream, needs future association with a IODevice
	TextStream();

	/// Creates a text stream associated with an IODevice
	TextStream(IODevice *device);

	/// Destroys the handle to the file, if exists.
	/// Guarantees the release of the object when going out of scope.
	~TextStream();

	/// Allow for querying if the stream is ready
	operator bool() const;

	/// Check if this stream reached the end of device / no more to read
	bool atEnd();

	/// Reads one character from the stream. It will be EOF if atEnd() is true.
	char readChar();

	/// Dislocating the reading pointer by offset bytes.
	bool seekByOffset(Int64 offset);

	/// Reads the next integer
	int readInt();

	/// Reads content until a line break is found
	String getLine();

	/// Overloads of operator<< to output strings
	TextStream& operator<<(const String &value);

	// Java-style parsing

/*	/// Advances in the file and attempts to find a valid string
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



		/// Overloads of operator>> for basic types.
		FileStream& operator>>(String &value);*/

private:
	IODevice *m_device;
};

PARABOLA_NAMESPACE_END
#endif