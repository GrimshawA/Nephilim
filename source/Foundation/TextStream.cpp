#include <Nephilim/Foundation/TextStream.h>
#include <Nephilim/IODevice.h>

#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

NEPHILIM_NS_BEGIN

	bool IsAlphaNumeric(char c){
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') && c == '.')return true;
		else return false;
	}

TextStream::TextStream() : m_device(NULL){

};

/// Creates a text stream associated with an IODevice
TextStream::TextStream(IODevice& device)
: m_device(&device)
{

};

TextStream::~TextStream(){

};

/// Check if this stream reached the end of device / no more to read
bool TextStream::atEnd()
{
	return m_device->atEnd();
};

/// Allow for querying if the stream is ready
TextStream::operator bool() const{
	return m_device->isReady();
};

char TextStream::readChar(){
	return m_device->getChar();
};

/// Read ahead without changing the reading marker
char TextStream::peek(std::size_t offset)
{
	// go forward in the stream
	seekByOffset(offset);

	// read the char in there
	char c = readChar();

	// seek back to the original place
	seekByOffset(-(int(offset) + 1));

	return c;
}

/// Dislocating the reading pointer by offset bytes.
bool TextStream::seekByOffset(Int64 offset){
	return m_device->seek(offset, SEEK_CUR);
};

/// Reads the next integer
int TextStream::readInt(){
	String number;
	char c;
	while((c = readChar()) >= '0' && c <= '9'){
		number += c;
	}
	return number.toInt();
};

/// Reads content until a line break is found
String TextStream::getLine(){
	String out;
	char c;
	while((c = readChar()) != EOF){
		if(c == '\n') break; // finish cycle earlier

		if(c != '\r')
			out.append(1,c);
	}
	//char c = readChar();
// 	while(c != '\n' ){
// 		if(c != '\r')
// 			out += c;
// 		c = readChar();
// 	}
	return out;
};

TextStream& TextStream::operator<<(const String &value){
	m_device->write(value.c_str(), value.size()*sizeof(char));
	return *this;
};


/*
	void TextStream::setDelimiter(char c){
		delimiter.clear();
		delimiter += c;
	};

	void TextStream::setDelimiter(const String &s){
		delimiter = s;
	};

	bool TextStream::hasNext(){
		Int64 pos = currentPosition();

		while(!atEnd()){
			char *buffer = new char[delimiter.size()];
			read(buffer, delimiter.size());

			if(delimiter != buffer){
				seek(pos); //go back
				return true;
			}
		}

		seek(pos); //go back
		return false;
	};

	String TextStream::nextString(){
		// \n always interrupts
		String output;

		bool stop = false;
		while(!stop){
			char c = readChar();
			if(c == '\n')stop = true;
			else{
				output += c; //keep reading until a end line is found or the delimiter

				// check if the delimiter was already found.
				if(output.compare(output.size() - 1 - delimiter.size(),delimiter.size(), delimiter) == 0 && delimiter.size() != output.size()){
					//the delimiter is the last characters, crop it out and stop and go back to the right place.
					output.erase(output.size() - delimiter.size() - 1, delimiter.size());
					stop = true;
					seekOffset(0 - delimiter.size());
				}

			}
		}

		return output;
	};

	bool TextStream::hasNextInt(){
		Int64 pos = currentPosition();
		bool result;
		String str = nextString();
		if(atoi(str.c_str()) == 0)result = false;
		else result = true;
		seek(pos); //go back
		return result;
	};

	int TextStream::nextInt(){
		return nextString().toInt();
	};

	bool TextStream::hasNextFloat(){
		Int64 pos = currentPosition();
		bool result;
		String str = nextString();
		if(atof(str.c_str()) == 0)result = false;
		else result = true;
		seek(pos); //go back
		return result;
	};

	float TextStream::nextFloat(){
		return nextString().toFloat();
	};


	void TextStream::skipLine(){
		char c;
		while((c = readChar()) != '\n'){
			if(c == EOF)break;
		};
	};

	void TextStream::skipChar(char c){
		while(readChar() == c);
	};

	void TextStream::skipUntil(char c){
		while(readChar() != c);
	};

	void TextStream::skipWhitespace(){
		while(::isspace(readChar()));
		seekOffset(-1);
	};

	String TextStream::getLine(){
		String out;
		char c = readChar();
		while(c != '\n' && c != '\r' && !atEnd()){
			out += c;
			c = readChar();
		}
		return out;
	};

	bool TextStream::findChar(char c){
		skipUntil(c);
		char cc = readChar();
		seekOffset(-2);
		if(cc == EOF) return false;
		else return true;
	};


	String TextStream::readWord(bool acceptNumbers, bool acceptUnderscore){
		String out;



		return out;
	};

	String TextStream::readBlock(char beginChar, char endChar){
		String output;
		int BeginStack = 0;
		char c;
		while((c=readChar()) != EOF){
			if(c == beginChar){
				BeginStack++;
				if(BeginStack > 1){
					output += c;
				}
			}
			else if(c == endChar){
				//done, output

				if(BeginStack == 1){
					//finished
					return output;
				}
				else if(BeginStack > 1){
					BeginStack--;
					output += c;
				}
				else
					std::cout<<"Parsing Error: Expecting '" <<beginChar<<"'."<<std::endl;

			}
			else{
				//not begin , and not end, either right character, or outside limits
				if(BeginStack >= 1){
					output += c;
				}
			}
		}

		return output;
	};



	FileStream& TextStream::operator>>(String &value){
		value = nextString();
		return *this;
	};
	*/
NEPHILIM_NS_END
