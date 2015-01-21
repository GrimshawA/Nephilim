#ifndef PARABOLA_ENGINEPROFILE_H
#define PARABOLA_ENGINEPROFILE_H

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class Engine;
/**
	\ingroup Core
	\class EngineProfile
	\brief Represents the complete configuration of the engine environment
*/	
class NEPHILIM_API EngineProfile{
public:
	/// Creates a default profile
	EngineProfile();

	/// Get the default profile settings 
	static EngineProfile DefaultProfile();

	/// Authorize engine's window
	bool run_window;

private:
	/// The parent engine
	Engine *myParent;
	friend class Engine;
};

NEPHILIM_NS_END
#endif