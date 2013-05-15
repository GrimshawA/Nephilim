#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <Nephilim/Event.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Font.h>
#include <Nephilim/Text.h>
#include <Nephilim/Clock.h>
using namespace nx;

#include "GameState.hpp"
#include "Generator.hpp"

class GameEngine;

class PlayState : public GameState
{
public:
	PlayState( bool replace = true );
	~PlayState();

	void Pause();
	void Resume();

	void HandleEvents( Event& event , Jumpy& game);
	void Update( Jumpy& game );
	void Draw( Renderer& screen  );

private:
	void ProcessInput();
	void CollisionDetection();
	void MoveObjects();
	void CalcGamePoints();

private:
	int mWndWidth;
	int mWndHeight;

	Generator mGenerator;

	bool touchLeft, touchRight;

	Texture mTexBackground;
	Sprite mSpBackground;
	FloatRect mRectBackground;
	float mToper;

	Texture mTexGameOver;
	Sprite mSpGameOver;
	Texture mTexPause;
	Sprite mSpPause;

	Texture mTexPlayer;
	Texture mTexPlayerGameover;
	Sprite mSpPlayer;

	Font mFreeFont;
	Text mScore;

	float mVelocityH; // Horizontal velocity
	float mVelocityV; // Vertical velocity
	float mDt; // Delta Time
	Clock mFPS;

	bool mFirstMove;
	bool mPause;
	bool mGameOver;
	float mPoints;
};

#endif // PLAYSTATE_HPP
