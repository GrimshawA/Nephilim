#include <memory>
#include <iostream>


#include "Jumpy.h"
#include "MenuState.hpp"

MenuState::MenuState( bool replace ) : GameState( replace )
{
	bgTex.loadFromFile( "img/menu.png" );

	bg.setTexture( bgTex, true );

	std::cout << "MenuState Init" << std::endl;
}

MenuState::~MenuState()
{
	std::cout << "MenuState Cleanup" << std::endl;
}

void MenuState::Pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::Resume()
{
	std::cout << "MenuState Resume" << std::endl;
}

void MenuState::HandleEvents( Event& event, Jumpy& game )
{

		switch( event.type )
		{			

			case Event::KeyPressed:
				switch( event.key.code )
				{
					case Keyboard::Escape:
						game.lastState();
						break;
				}
				break;
		}

}

void MenuState::Update( Jumpy& game ) 
{

}

void MenuState::Draw(Renderer& screen  )
{
	// Clear the previous drawing
	//screen.clear();
	screen.draw( bg );
}

