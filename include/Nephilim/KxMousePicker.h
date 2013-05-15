#ifndef KxMousePicker_h__
#define KxMousePicker_h__

#include "Platform.h"

class b2MouseJoint;

NEPHILIM_NS_BEGIN

class KxScene;

class KxMousePicker
{
public:

	KxMousePicker();

	void attachAt(float x, float y);

	void update(float x, float y);

	void detach();

	KxScene* scene;
	b2MouseJoint* joint;
};

NEPHILIM_NS_END
#endif // KxMousePicker_h__
