#ifndef NephilimAxSignal_h__
#define NephilimAxSignal_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Animation/Animation.h>

#include <sigc++/sigc++.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AxSignal
	\brief Emits a signal when played
*/
class NEPHILIM_API AxSignal : public Animation
{
public:
	sigc::signal<void> event;
};

NEPHILIM_NS_END
#endif // NephilimAxSignal_h__
