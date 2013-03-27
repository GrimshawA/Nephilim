#include "Nephilim/Logger.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Simply outputs the string into the stdout
void Logger::fastLog(const String &output){
	cout<<output<<endl;
};

PARABOLA_NAMESPACE_END