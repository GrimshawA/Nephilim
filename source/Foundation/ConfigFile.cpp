#include <Nephilim/Foundation/ConfigFile.h>

NEPHILIM_NS_BEGIN

/// Creates a default profile
EngineProfile::EngineProfile(){
	myParent = NULL;
};

/// Get the default profile settings 
EngineProfile EngineProfile::DefaultProfile(){
	EngineProfile profile;
	profile.run_window = true;
	return profile;
};

NEPHILIM_NS_END