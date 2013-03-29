#ifndef ForgeNodeCircle_h__
#define ForgeNodeCircle_h__

#include "Platform.h"
#include "ForgeNode.h"
#include "Vectors.h"

#include <iostream>

NEPHILIM_NS_BEGIN

class ForgeNodeCircle : public ForgeWorldNode{
public:
	ForgeNodeCircle(Vec2f position, float radius){
		m_p = position;
		m_r = radius;
	}

	Vec2f m_p;
	float m_r;

	void draw(Renderer* renderer){
		renderer->drawDebugCircle(m_p, m_r, Vec2f(), Color::Red);
		//std::cout<<"drawn";
	}
};

NEPHILIM_NS_END
#endif // ForgeNodeCircle_h__