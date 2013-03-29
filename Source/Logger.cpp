#include "Nephilim/Logger.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Simply outputs the string into the stdout
void Logger::fastLog(const String &output){
	cout<<output<<endl;
};

NEPHILIM_NS_END