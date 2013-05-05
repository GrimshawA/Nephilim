#include "Platform.hpp"

#include <stdlib.h>

Platform::Platform() :
	Type( 0 ),
	moveType( 0 ),
	relPos( 0 ),
	Direction( 1 ),
	Speed( 80 )
{

}

void Platform::update(float aDt)
{
	if( Type == 4)
	{
		if(moveType == 1) // left-right
		{
			sprite.setPosition(sprite.getPosition().x + Speed * aDt * Direction, sprite.getPosition().y);
		}
		else if(moveType == 2) // up-down
		{
			sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + Speed * aDt * Direction);
		}
		else
			moveType = 1 + (rand() % 2);

		relPos += Speed * aDt * Direction;
		if(relPos >= 60)
			Direction = -1;
		else if(relPos <= -60)
			Direction = 1;
	}

}
