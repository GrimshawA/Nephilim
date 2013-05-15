#ifndef NephilimInputGrabber_h__
#define NephilimInputGrabber_h__

#include "Platform.h"
#include "Event.h"

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class InputGrabber
	\brief Proxy to catch and handle events easily
*/
class NEPHILIM_API InputGrabber
{
public:
	InputGrabber()
	{
		
	}

	void update(const Event& event)
	{
		if(event.type == Event::KeyPressed)
		{
			m_keys[event.key.code] = true;
		}
		else if(event.type == Event::KeyReleased)
		{
			m_keys[event.key.code] = false;
		}
	}

	bool getKey(Keyboard::Key key)
	{
		if(m_keys.find(key) == m_keys.end())
		{
			m_keys[key] = false;
		}
		return m_keys[key];
	}

	std::map<Keyboard::Key, bool> m_keys;
};

NEPHILIM_NS_END
#endif // NephilimInputGrabber_h__
