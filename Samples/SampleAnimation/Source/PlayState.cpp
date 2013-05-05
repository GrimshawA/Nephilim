#include <memory>
#include <iostream>
#include <sstream>

#include <Nephilim/Sprite.h>
#include <Nephilim/Surface.h>
#include <SFML/Graphics.hpp>

#include "Jumpy.h"

#ifdef NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#endif

#include <Nephilim/Renderer.h>

#include "PlayState.hpp"
 
PlayState::PlayState( bool replace ) :
	GameState( replace ),
	mWndWidth( 350 ),
	mWndHeight( 570 ),
	mGenerator( mWndWidth, mWndHeight ),
	mVelocityH( 0.0f ),
	mVelocityV( 0.0f ),
	mFirstMove( false ),
	mPause( false ),
	mGameOver( false ),
	mPoints( 0.f ),
	touchLeft(false),
	touchRight(false)
{
	mRectBackground = FloatRect( 0, 0, mWndWidth*2, mWndHeight ); // Background shall be moved around
	mToper = 0.f;

	if( !mTexBackground.loadFromFile( "res/background.png" ) )
		std::cout << "Resource 'background.png' is missing!" << std::endl;
	mSpBackground.setTexture( mTexBackground, true );
	mSpBackground.setTextureRect( mRectBackground );

	if( !mTexGameOver.loadFromFile( "res/gameover2.png" ) )
		std::cout << "Resource 'gameover2.png' is missing!" << std::endl;
	mSpGameOver.setTexture( mTexGameOver, true );
	mSpGameOver.setPosition( 25.f, 185.f );

	if( !mTexPause.loadFromFile( "res/pause.png" ) )
		std::cout << "Resource 'pause.png' is missing!" << std::endl;
	mSpPause.setTexture( mTexPause, true );
	mSpPause.setPosition( 25.f, 185.f );

	if( !mTexPlayer.loadFromFile( "res/player.png" ) )
		std::cout << "Resource 'player.png' is missing!" << std::endl;
	if( !mTexPlayerGameover.loadFromFile( "res/player-go.png" ) )
		std::cout << "Resource 'player-go.png' is missing!" << std::endl;
	mSpPlayer.setTexture( mTexPlayer, true );
	mSpPlayer.setPosition( mWndWidth/2.f-25.f, mWndHeight/2.f-1.f ); // Center the player

	if( !mFreeFont.loadFromFile( "res/FreeSansBold.ttf" ) )
		std::cout << "Resource 'FreeSansBold.ttf' is missing!" << std::endl;
	mScore.setFont( mFreeFont );
	mScore.setCharacterSize( 20U );
	mScore.setString( "Doodle Jumper" );
	mScore.setColor( Color( 153, 34, 17 ) );
	mScore.setPosition( 10, 10 );

	std::cout << "PlayState Init" << std::endl;
}

PlayState::~PlayState()
{
	std::cout << "PlayState Cleanup" << std::endl;
}

void PlayState::Pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::Resume()
{
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::HandleEvents( Event& event , Jumpy& game)
{
		switch( event.type )
		{
		
		case Event::TouchPressed:
			if(event.x < game.getSurface().getWidth()  / 2){ touchLeft = true;touchRight = false;}
			else{ touchLeft = false; touchRight = true;}
			break;
		case Event::TouchMoved: 
			if(event.x < game.getSurface().getWidth()  / 2){ touchLeft = true;touchRight = false;}
			else{ touchLeft = false; touchRight = true;}
			break;
		case Event::TouchReleased:
			{
				touchRight = touchLeft = false;
				if( mGameOver ) // Restart game
					next = new PlayState(false);
			}
			
			break;

			case Event::LostFocus:
				mPause = true;
				break;
			case Event::GainedFocus:
				mPause = false;
				break;
			case Event::MouseButtonReleased:
			case Event::KeyReleased:
				if( mGameOver ) // Restart game
					next = new PlayState(false);
				break;
	
		}
	
}

void PlayState::Update(Jumpy& game )
{
	// Get delta time
	mDt = mFPS.getElapsedTime().asSeconds();
	mFPS.reset();

	// Check for game over
	if( mSpPlayer.getPosition().y + mSpPlayer.getGlobalBounds().height > mWndHeight )
	{
		if( mFirstMove )
		{
			mSpPlayer.setTexture( mTexPlayerGameover );
			mGameOver = true;
		}
		else // Prevent dying on start
			mVelocityV = 300.f;
	}

	if(mGameOver || mPause)
		return;

	ProcessInput();
	CollisionDetection();
	MoveObjects();
	mGenerator.update( mDt );
	CalcGamePoints();

	// Player should fall
	mVelocityV -= 280 * mDt;
}

void PlayState::Draw( Renderer& screen )
{
	// Clear the previous drawing
	//screen.clear();
	screen.draw( mSpBackground );
	
	if( mGameOver )
		screen.draw( mSpGameOver );
	else
	{
		mGenerator.draw( screen );
		screen.draw( mSpPlayer );

		if( mPause )
			screen.draw( mSpPause );
	}

	screen.draw( mScore );
}

void PlayState::ProcessInput()
{
#ifdef NEPHILIM_DESKTOP
	// Stop horizontal movement
	if(!sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && !sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && mVelocityH < 20.0f && mVelocityH > -20.0f )
		mVelocityH = 0;
	// Deaccelerate
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mVelocityH < 0)
		mVelocityH += 280.0f * mDt;
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mVelocityH > 0)
		mVelocityH -= 280.0f * mDt;
	// Accelerate
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		mVelocityH = 120.0f;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		mVelocityH = -120.0f;
	// Stop if both keys are pressed
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		mVelocityH = 0;

#else
	// Stop horizontal movement
	if(!touchLeft && !touchRight && mVelocityH < 20.0f && mVelocityH > -20.0f )
		mVelocityH = 0;
	// Deaccelerate
	else if(!touchLeft && !touchRight && mVelocityH < 0)
		mVelocityH += 280.0f * mDt;
	else if(!touchLeft && !touchRight && mVelocityH > 0)
		mVelocityH -= 280.0f * mDt;
	// Accelerate
	else if(!touchLeft && touchRight)
		mVelocityH = 120.0f;
	else if(touchLeft && !touchRight)
		mVelocityH = -120.0f;
#endif
}

void PlayState::CollisionDetection()
{
	if( mVelocityV < 0.f )
	{
		float newVelocity = mGenerator.collision( mSpPlayer );
		if( newVelocity != 0.f )
		{
			mVelocityV = newVelocity;
#ifdef NEPHILIM_ANDROID
			AndroidInterface::vibrate(100);
#endif
		}
	}
}

void PlayState::MoveObjects()
{
	// Get current player location
	vec2 pos = mSpPlayer.getPosition();

	// Background & Platforms are moving
	if(mSpPlayer.getPosition().y <= mWndHeight / 3.f)
	{
		mFirstMove = true;

		if(mVelocityV < 0) // Player is still falling
			mSpPlayer.setPosition( pos.x+( mVelocityH * mDt ), pos.y + 30 * mDt);
		else // Keep the player's y position fixed
			mSpPlayer.setPosition( pos.x+( mVelocityH * mDt ), pos.y);
		
		// Move background
		mToper -= mVelocityV * mDt;
		mRectBackground.top = static_cast<int>( mToper );
		mSpBackground.setTextureRect(mRectBackground);
		if(mRectBackground.top <= 0)
		{
			mRectBackground.top = 570;
			mToper = 570.0f;
		}

		mGenerator.move( mVelocityV * mDt );
	}
	else // No need to move the background
		mSpPlayer.setPosition( pos.x+( mVelocityH * mDt ), pos.y - mVelocityV * mDt );

	// Prevent player from leaving the playground
	if( mSpPlayer.getPosition().x < 0.f )
		mSpPlayer.setPosition( 0.f, mSpPlayer.getPosition().y );
	else if( mSpPlayer.getPosition().x > mWndWidth - mSpPlayer.getGlobalBounds().width )
		mSpPlayer.setPosition( mWndWidth - mSpPlayer.getGlobalBounds().width, mSpPlayer.getPosition().y );
}

void PlayState::CalcGamePoints()
{
	// Game points calculation
	mPoints += (mVelocityV * mDt) / 10.f;
	if(mPoints < 0)
		mPoints = 0;

	std::ostringstream out;
	out << static_cast< int >(mPoints);
	mScore.setString(out.str());
}