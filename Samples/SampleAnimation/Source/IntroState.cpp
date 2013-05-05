#include <memory>
#include <iostream>

#include "IntroState.hpp"
#include "PlayState.hpp"
#include "Jumpy.h"

IntroState::IntroState( bool replace ) : GameState( replace ), mHover( false )
{
	if( !mTexTitle.loadFromFile( "res/title.png" ) )
		std::cout << "Resource 'title.png' is missing!" << std::endl;
	mSpTitle.setTexture( mTexTitle, true );

	if( !mTexHover.loadFromFile( "res/hover.png" ) )
		std::cout << "Resource 'hover.png' is missing!" << std::endl;
	mSpHover.setTexture( mTexHover );
	mSpHover.setPosition( 0.0f, 461.0f );

	mHoverRect = FloatRect( 0, 200, 550, 360 );

	std::cout << "IntroState Init" << std::endl;
}

IntroState::~IntroState()
{
	std::cout << "IntroState Cleanup" << std::endl;
}

void IntroState::Pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::Resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::HandleEvents( Event& event, Jumpy& game )
{
		switch( event.type )
		{
		

			case Event::MouseButtonReleased:
				if( mHoverRect.contains(event.mouseButton.x, event.mouseButton.y) ) 
				{
					next = new PlayState(false);
				}
				break;	

			case Event::TouchReleased:

				if( mHoverRect.contains(event.x * 320 / 350, event.y * 570 / 480) ) 
				{
					Log("Starting PlayState now!");
					next = new PlayState(false);
				}
				Log("Touch Released: %f, %f",event.x * 320 / 350, event.y * 570 / 480);
				break;
		}
}

void IntroState::Update( Jumpy& game ) 
{
	
}

void IntroState::Draw( Renderer& screen  ) 
{
	// Clear the previous drawing
	//screen.clear();

	screen.draw( mSpTitle );

	if( mHover )
		screen.draw( mSpHover );

}

