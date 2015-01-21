#include <Nephilim/Animation/AxList.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

AxList::~AxList()
{
	std::list<AxBase*>::iterator it = m_animations.begin();
	while( it != m_animations.end())
	{
		delete (*it);
		it++;
	}
}

void AxList::update(float delta)
{
	std::list<AxBase*>::iterator it = m_animations.begin();
	while( it != m_animations.end())
	{
		(*it)->update(delta);

		if((*it)->isOver())
		{
			delete (*it);
			it = m_animations.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void AxList::commit(AxBase* animation)
{
	m_animations.push_back(animation);
}

NEPHILIM_NS_END