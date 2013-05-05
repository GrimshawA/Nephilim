#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

#include <Nephilim/Event.h>
#include <Nephilim/Sprite.h>
using namespace nx;

class GameEngine;

class MenuState : public GameState
{
public:
	MenuState( bool replace = true );
	~MenuState();

	void Pause();
	void Resume();

	void HandleEvents( Event& event , Jumpy& game);
	void Update( Jumpy& game );
	void Draw( Renderer& screen  );

private:

	Texture bgTex;
	Sprite bg;
};

#endif // MENUSTATE_HPP
