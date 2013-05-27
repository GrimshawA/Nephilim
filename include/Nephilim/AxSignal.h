#ifndef NephilimAxSignal_h__
#define NephilimAxSignal_h__

#include "Platform.h"
#include "AxBase.h"
#include "Signals.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AxSignal
	\brief Emits a signal when played
*/
class NEPHILIM_API AxSignal : public AxBase
{
public:
	sigc::signal<void> event;
};

NEPHILIM_NS_END
#endif // NephilimAxSignal_h__
