#include "Nephilim/EngineProfile.h"

PARABOLA_NAMESPACE_BEGIN

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

PARABOLA_NAMESPACE_END