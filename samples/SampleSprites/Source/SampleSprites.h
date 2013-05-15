#ifndef SampleSprites_h__
#define SampleSprites_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Text.h>
#include <Nephilim/Font.h>
#include <Nephilim/Clock.h>
#include <Nephilim/View.h>
#include <Nephilim/CircleShape.h>
using namespace nx;

#include "Enemy.h"

struct menuSystem
{
	Text titleText, playText, quitText, scoreText;
};

class SampleSprites : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);


	Clock gameClock, levelClock, scoreClock;
	unsigned int level, levelCounter;
	float Score;
	Font mainFont;
	Text textOverlay;
	View mainView;
	float playerSize;
	CircleShape player;


	std::vector<Enemy*> Enemies;
	Color enemyColor;
	int fpsLimit;
	bool gameStatus;
	menuSystem gameMenu;

};
#endif // SampleSprites_h__
