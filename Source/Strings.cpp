#include "Nephilim/Strings.h"
#include "Nephilim/StringList.h"
#include <sstream>
#include <stdlib.h>

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

NEPHILIM_NS_BEGIN

	// Constructors
	String::String() : std::string(){

	};

	String::String(const String& str) : std::string(str){

	};

	String::String(const String& str, size_t pos, size_t n) : std::string(str, pos, n){

	};

	String::String(const char * s, size_t n) : std::string(s, n){

	};

	String::String(const char * s) : std::string(s){

	};

	String::String(size_t n, char c) : std::string(n, c){

	};

	String::String(const std::string &s) : std::string(s){
	
	};

	void String::removeUntil(char c){
		erase(0, find_first_of(c));		
	};

	void String::removeUntilReverse(char c){
		size_t ocurr = find_last_of(c);
		if(ocurr == npos)ocurr = 0;
		erase(ocurr, npos);
	};

/*#ifdef NEPHILIM_WINDOWS
	std::wstring String::toWide(){
		int len;
		int slength = (int)(*this).length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, (*this).c_str(), slength, 0, 0); 
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, (*this).c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

	/// Converts a wide string and sets this string with its content
	void String::fromWide(std::wstring &wide){
		this->assign(wide.begin(), wide.end());
	};
#endif*/

	void String::removeCharacter(char c){	
		size_type it;
		while((it = find_first_of(c, 0)) != npos)erase(it, 1);
	};

	int String::toInt(){
		return atoi(this->c_str());
	}

	float String::toFloat(){
		return (float)atof(this->c_str());
	};

	double String::toDouble(){
		return atof(this->c_str());
	};

	void String::toLowerCase(){
		for(unsigned int i = 0; i < length(); i++){
			(*this)[i] = tolower((*this)[i]);
		}
	}

	/// Replaces all occurrences of a character
	void String::replaceCharacter(char replace, char with){
		for(unsigned int i = 0; i < length(); i++){
			if((*this)[i] == replace) (*this)[i] = with;
		}
	};

	bool String::toBoolean(){
		String low = *this;
		low.toLowerCase();
		if(low == "true")
			return true;
		else return false;
	}

	StringList String::split(String splitBy, int limitCount){
		StringList MyStrList;
		unsigned int Iter = 0;
		String MyStr = *this;
		String Current;

		for(unsigned int i = 0; i < MyStr.length(); i++){
			if(MyStr[i] == splitBy[Iter]){
				Iter++;
			}
			else{
				//Break a partial match
				Iter = 0;
			}

			Current += MyStr[i];

			if(Iter == splitBy.length()){
				if(limitCount != 0 && MyStrList.size() == limitCount)
					continue;
				Current.erase(Current.length() - Iter, Current.length());
				MyStrList.push_back(Current);
				Current.clear();
				Iter = 0; 
			}
		}
		Current.erase(Current.length() - Iter, Current.length());
		MyStrList.push_back(Current);

		return MyStrList;

	};

	/// Splits
	void String::split(String s, char delim, StringList &elems){
		std::stringstream ss(s);
		String item;
		while(std::getline(ss, item, delim)) {
			if(!item.empty())
				elems.push_back(item);
		}
	};

	StringList String::split(char c, int limitCount){
		StringList elems;
		String mm = *this;
		split(mm, c, elems);
		return elems;
	};

	bool String::startsWith(const String &str){
		size_t result = find(str);
		if(result == 0)return true;
		else return false;
	}

	bool String::endsWith(const String &str){
		size_t result = find(str);
		if(result == length()-str.length())return true;
		else return false;
	}

	bool String::contains(const String &str){
		if(find(str) == npos)return false;
		else return true;
	};

	/// Creates a string from an int
	String String::number(int n){
		std::stringstream res;
		res << n;
		return res.str();
	};

	/// Creates a string from an unsigned int
	String String::number(unsigned int n){
		std::stringstream res;
		res << n;
		return res.str();
	};

	/// Creates a string from a float
	String String::number(float n){
		std::stringstream res;
		res << n;
		return res.str();
	};

	/// Creates a string from a double
	String String::number(double n){
		std::stringstream res;
		res << n;
		return res.str();
	};

	/// Creates a string from a long
	String String::number(long n){
		std::stringstream res;
		res << n;
		return res.str();
	};

	/// Creates a string from an unsigned long
	String String::number(unsigned long n){
		std::stringstream res;
		res << n;
		return res.str();
	};

	String::operator const char*(){
		return this->c_str();
	}

	String& String::operator=(const std::string &str){		
		clear();
		append(str);
		return *this;
	};

	String& String::operator=(const char* c){
		clear();
		append(c);
		return *this;
	};

	String& String::operator+=(const String &str){
		append(str);
		return *this;
	};

	String& String::operator+=(char c){
		append(1,c);
		return *this;
	};

	const String String::operator+(const String &str) const{
		String out = *this;
		out.append(str);
		return out;
	}

	const String String::operator+(const char* c) const{
		String out = *this;
		out.append(c);
		return out;
	};

	/// Overload for operator[] for int literals - set operator
	const char& String::operator[](int pos) const{
		return std::string::operator []((size_t)pos);
	};

	/// Overload for operator[] for int literals - get operator
	char& String::operator[](int pos){
		return std::string::operator []((size_t)pos);

	};

NEPHILIM_NS_END