#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include <Nephilim/Event.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/Texture.h>
using namespace nx;

#include "GameState.hpp"

class GameEngine;

class IntroState : public GameState
{
public:
	IntroState( bool replace = true );
	~IntroState();

	void Pause();
	void Resume();

	void HandleEvents( Event& event, Jumpy& game );
	void Update( Jumpy& game );
	void Draw( Renderer& screen );

private:
	Texture mTexTitle;
	Texture mTexHover;
	Sprite mSpTitle;
	Sprite mSpHover;

	FloatRect mHoverRect;
	bool mHover;
};

#endif // INTROSTATE_HPP
