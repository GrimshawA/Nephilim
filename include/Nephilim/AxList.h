#ifndef NephilimAxList_h__
#define NephilimAxList_h__

#include <Nephilim/Platform.h>

#include "AxBase.h"

#include <list>

NEPHILIM_NS_BEGIN


/**
	\ingroup Animation
	\class AxList
	\brief Processes multiple animations at the same time

	All animations are destroyed after finishing playing.
*/
class NEPHILIM_API AxList
{
public:

	/// Delete all animations
	~AxList();

	/// Commit a new animation for processing
	void commit(AxBase* animation);

	/// Updates the list of animations
	void update(float delta);

	std::list<AxBase*> m_animations; ///< Processing animation list
};

NEPHILIM_NS_END
#endif // NephilimAxList_h__