#include "Generator.hpp"

#include <Nephilim/Renderer.h>
using namespace nx;
#include <iostream>

Generator::Generator( int aWndWidth, int aWndHeight ) :
	mWndWidth( static_cast<float>( aWndWidth ) ),
	mWndHeight( static_cast<float>( aWndHeight ) ),
	mTotalMove( 0.f )
{
	std::srand( static_cast<unsigned int>( time( 0 ) ) );

	if(!mTexSolid.loadFromFile( "res/platform-solid.png" ) )
		std::cout << "Resource 'platform-solid.png' is missing!" << std::endl;
	if(!mTexUnstable.loadFromFile( "res/platform-unstable.png" ) )
		std::cout << "Resource 'platform-unstable.png' is missing!" << std::endl;
	if(!mTexJump.loadFromFile( "res/platform-jump.png" ) )
		std::cout << "Resource 'platform-jump.png' is missing!" << std::endl;
	if(!mTexFloat.loadFromFile( "res/platform-float.png" ) )
		std::cout << "Resource 'platform-float.png' is missing!" << std::endl;

	generateInit();
}

void Generator::generateInit()
{
	for(int y=0; y < 7; y++)
		for(int x=0; x < 3; x++)
		{
			float genX = static_cast<float>( randomizer( x * 115, x * 115 + 45 ) );
			float genY = static_cast<float>( ( mWndHeight - randomizer( y * 114, y * 114 + 84 ) ) + 10 );
			generate( genX, genY );
		}
}

void Generator::generateNext()
{
	mTotalMove = 0.f;

    for(int x = 0; x < 2; ++x)
    {
		float genX = static_cast<float>( randomizer( x*140, x*140+140 ) );
		float genY = static_cast<float>( -randomizer( 84, 0 ) );
		generate( genX, genY );
    }
}

void Generator::generate( float aGenX, float aGenY )
{
	Platform genPlatform;
	genPlatform.sprite.setPosition( aGenX, aGenY );

	int rand = randomizer( 1,12 );

	// 1-2 shouldn't create anything

	// Solid platform
	if( rand >= 3 && rand <= 5 )
	{
		genPlatform.sprite.setTexture( mTexSolid, true );
		genPlatform.Type = 1;
	}
	// Unstable platform
	else if( rand >= 6 && rand <= 8 )
	{
		genPlatform.sprite.setTexture( mTexUnstable, true );
		genPlatform.Type = 2;
	}
	// Jump platform
	else if( rand >= 9 && rand <= 10 )
	{
		genPlatform.sprite.setTexture( mTexJump, true );
		genPlatform.Type = 3;
	}
	// Floating platform
	else if( rand >= 11 && rand <= 12 )
	{
		genPlatform.sprite.setTexture( mTexFloat, true );
		genPlatform.Type = 4;
	}

	mPlatforms.push_back( genPlatform );
}

int Generator::randomizer(int aMin, int aMax)
{
	return aMin + (rand() % (aMax - aMin + 1));
}

void Generator::update( float aDt )
{
	for( std::list<Platform>::iterator it = mPlatforms.begin(); it != mPlatforms.end(); it++ )
		it->update( aDt );
}

void Generator::move( float aDistance )
{
	// Move platforms
	for( std::list<Platform>::iterator it = mPlatforms.begin(); it != mPlatforms.end(); it++ )
	{
		// Move
		it->sprite.setPosition( it->sprite.getPosition().x, it->sprite.getPosition().y + aDistance );
		
		// Earse the platform if it falls out of the screen
		if( it->sprite.getPosition().y > mWndHeight + 60 )
			it = mPlatforms.erase( it );
	}

	mTotalMove += aDistance;

	// Enough space is needed for platform generation
	if( mTotalMove > 100 )
		generateNext();
}

float Generator::collision( const Sprite& aPlayer )
{
	FloatRect playerRect( aPlayer.getPosition().x + 10, aPlayer.getPosition().y+40, aPlayer.getGlobalBounds().width - 15.f, 10.f );
    
	for( std::list<Platform>::iterator it = mPlatforms.begin(); it != mPlatforms.end(); it++ )
    {
		FloatRect platformRect( it->sprite.getPosition().x, it->sprite.getPosition().y, it->sprite.getGlobalBounds().width, 5.f );

		if( playerRect.intersects( platformRect ) )
        {
			if( it->Type == 1 || it->Type == 4 )
				return 400.f;
			else if( it->Type == 2 ) // Unstable
			{
				it = mPlatforms.erase( it );
				return 380.f;
			}
			else if( it->Type == 3 ) // Jump
				return 600.f;

			// @TODO
			// Jede Plattform Berührung kostet 10p
			/*if(fPoints >= 10)
			fPoints -= 10;
			break;*/
        }
    }

	return 0.f;
}

void Generator::draw( Renderer& target ) const
{
	for( std::list<Platform>::const_iterator it = mPlatforms.begin(); it != mPlatforms.end(); it++ )
	{
		const Sprite& sprite = it->sprite;
		target.draw( const_cast<Sprite&>(sprite) );
	}
}
