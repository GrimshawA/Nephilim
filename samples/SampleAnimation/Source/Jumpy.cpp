#include "Jumpy.h"

#include "IntroState.hpp"

#include <Nephilim/Surface.h>

#ifdef NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#endif

void Jumpy::onCreate()
{
	getSurface().setSize(350, 570);
	getRenderer()->setDefaultViewport();

	m_running = true;
	states.push(new IntroState(false));
	nextState();	
}

void Jumpy::nextState()
{
	// there needs to be a state
	if ( !states.empty() )
	{
		GameState* temp = states.top()->Next();

		// only change states if there's a next one existing
		if( temp != NULL )
		{
			// replace the running state
			if( temp->isReplacing() )
				states.pop();
			// pause the running state
			else
				states.top()->Pause();

			states.push( temp );
		}
	}
}

void Jumpy::lastState()
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


void Jumpy::onEvent(Event &event)
{
	switch( event.type )
	{
	case Event::Closed:
		close();   
		break;

	case Event::KeyPressed:
		if(event.key.code == Keyboard::AndroidBack)
		{
			#ifdef NEPHILIM_ANDROID
				AndroidInterface::closeActivity();
			#endif
		}
		break;
	}
	


	// let the state handle events
	states.top()->HandleEvents( event, *this );
}

void Jumpy::onUpdate(Time time)
{ 
	nextState();

	// let the state update the game
	states.top()->Update( *this );
}

void Jumpy::onRender()
{
	getRenderer()->setProjectionMatrix(View(0,0,350,570).getMatrix());

	// let the state draw the screen
	states.top()->Draw( *getRenderer() );
}
