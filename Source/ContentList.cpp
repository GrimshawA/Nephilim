#include "Nephilim/ContentList.h"

NEPHILIM_NS_BEGIN

/// Creates an yet empty list of content
ContentList::ContentList() : myLocked(false){
	
};

/// Locks this content list, to prevent removal - Bank utilities
void ContentList::lock(){
	myLocked = true;
};

/// Unlocks this content list, allowing removal - Bank utilities
void ContentList::unlock(){
	myLocked = false;
};

/// Check if it is locked
bool ContentList::locked(){
	return myLocked;
};

NEPHILIM_NS_END