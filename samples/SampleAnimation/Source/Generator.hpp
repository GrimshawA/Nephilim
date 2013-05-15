#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <cstdlib>
#include <ctime>
#include <list>

#include "Platform.hpp"

class Generator
{
public:
	Generator( int aWndWidth, int aWndHeight );

	void update( float aDt );
	void move( float aDistance );
	float collision( const Sprite& aPlayer );
	void draw( Renderer& target ) const;

private:
	void generate( float aGenX, float aGenY );
	void generateInit();
	void generateNext();
	int randomizer( int aMin, int aMax );

private:
	float mWndWidth;
	float mWndHeight;
	std::list<Platform> mPlatforms;
	float mTotalMove;

	Texture mTexSolid;
	Texture mTexUnstable;
	Texture mTexJump;
	Texture mTexFloat;
};

#endif // GENERATOR_HPP
