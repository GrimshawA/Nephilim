#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <Nephilim/Sprite.h>
using namespace nx;

class Platform
{
public:
	Platform();

	Sprite sprite;
	int Type;
   
	void update( float aDt );

private:
	int moveType;
	float relPos;
	int Direction;
	int Speed;
};

#endif // PLATFORM_HPP
