#include "GameEngine.hpp"

#include <memory>
#include <iostream>
#include "GameState.hpp"

GameEngine::GameEngine( const std::string& title, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen ) :
	m_running( false ),
	m_fullscreen( fullscreen )
{
	int flags = 0;

	if( fullscreen )
		flags = sf::Style::Fullscreen;
	else
		flags = sf::Style::Default;

	if( !mApplicationIcon.loadFromFile("res/jumpy.png") )
		std::cout << "Resource 'jumpy.png' is missing!" << std::endl;

	// Create render window
	screen.create( sf::VideoMode( width, height, bpp ), title, flags );
	screen.setFramerateLimit( 60 );
	screen.setIcon( mApplicationIcon.getSize().x, mApplicationIcon.getSize().y, mApplicationIcon.getPixelsPtr() );

	std::cout << "GameEngine Init" << std::endl;
}

void GameEngine::Run( std::unique_ptr<GameState> state )
{
	m_running = true;
	
	states.push( std::move( state ) );
}

void GameEngine::NextState() 
{
	// there needs to be a state
	if ( !states.empty() )
	{
		std::unique_ptr<GameState> temp = states.top()->Next();

		// only change states if there's a next one existing
		if( temp != nullptr )
		{
			// replace the running state
			if( temp->isReplacing() )
				states.pop();
			// pause the running state
			else
				states.top()->Pause();
			
			states.push( std::move( temp ) );
		}
	}
}

void GameEngine::LastState()
{
	// cleanup the current state
	if ( !states.empty() )
	{
		states.pop();
	}

	// resume previous state
	if ( !states.empty() )
	{
		states.top()->Resume();
	}
}

void GameEngine::HandleEvents() 
{
	// let the state handle events
	states.top()->HandleEvents( *this );
}

void GameEngine::Update() 
{
	// let the state update the game
	states.top()->Update( *this );
}

void GameEngine::Draw() 
{
	// let the state draw the screen
	states.top()->Draw( *this );
}

