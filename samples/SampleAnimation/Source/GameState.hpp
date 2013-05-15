#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

#include <Nephilim/Event.h>
using namespace nx;

class Jumpy;

class GameState
{
public:
	GameState( bool replace = true ) : replacing( replace ), next(NULL) {}
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents( Event& event, Jumpy& game ) = 0;
	virtual void Update( Jumpy& game ) = 0;
	virtual void Draw(  Renderer& screen) = 0;

	GameState* Next()
	{
		return next;
	}

	/*void ChangeState( GameEngine& game, std::unique_ptr<GameState> state )
	{
		game.ChangeState( std::move( state ) );
	}*/

	bool isReplacing()
	{
		return replacing;
	}

protected:
	bool replacing;
	GameState* next;
};

#endif // GAMESTATE_HPP
