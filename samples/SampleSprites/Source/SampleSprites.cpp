#include "SampleSprites.h"

#include <Nephilim/View.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/Surface.h>

#ifdef NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#endif


#include <iostream>
using namespace std;

#include <Nephilim/MMath.h>

bool collides(vec2 enemyPos, vec2 point)
{
	//return FloatRect (enemyPos.x, enemyPos.y, 20,15).contains(point.x, point.y);
	return Math::distance(enemyPos, point) < 10;
}

Color incrementColor(Color &color)
{
	if(color.a > 254)
	{
		if(color.r > 80)
			color.r--;
		else if(color.g > 80)
			color.g--;
		else if(color.b > 80)
			color.b--;
		else
			color.a--;
	}
	else
	{
		if(color.r < 255)
			color.r++;
		else if(color.g < 255)
			color.g++;
		else if(color.b < 255)
			color.b++;
		else
			color.a = 255;
	}
	return color;
}

vec2 sinMovement(vec2 currentPosition, vec2 &startingPoint, vec2 &Destination, vec2 &linearPosition, float &angle, float deltaTime)
{
	angle += 0.01 * deltaTime;
	vec2 direction = Destination - startingPoint;
	direction.normalize();
	float sinDeviation = sin(2 * angle) - 0.5;
	vec2 deviation(-direction.y, direction.x);
	deviation.x *= sinDeviation * 30.f;
	deviation.y *= sinDeviation * 30.f;
	linearPosition.x += direction.x * 300.f * deltaTime/1000.f;
	linearPosition.y += direction.y * 300.f * deltaTime/1000.f;
	return linearPosition + deviation;
}

vec2 linearMovement(vec2 currentPosition, vec2 &startingPoint, vec2 &Destination, vec2 &linearPosition, float &angle, float deltaTime)
{
	vec2 direction = Destination - startingPoint;
	direction.normalize();
	linearPosition.x += direction.x * 300.f * deltaTime/1000.f;
	linearPosition.y += direction.y * 300.f * deltaTime/1000.f;
	return linearPosition;
};


void SampleSprites::onCreate()
{	
	level = 1;
	levelCounter = 0;
	Score = 0.f;
	scoreClock.reset();

	if(mainFont.loadFromFile("DejaVuSans.ttf"))
	{
		Log("Loaded DejaVuSans.");
	}
	else
	{
		Log("Failed to load main font.");
	}

	textOverlay.setFont(mainFont);
	textOverlay.setCharacterSize(12);
	textOverlay.setString("Current FPS: ");
	textOverlay.setPosition(5,5);

	//sf::RenderWindow mainWindow {sf::VideoMode{800, 600}, "LD26"};
	//mainWindow.setMouseCursorVisible(false);

	
	mainView.setRect(0.f,0.f,static_cast<float>(getSurface().getSize().x), static_cast<float>(getSurface().getSize().y));
	//mainView.setViewport(FloatRect {0.f, 0.f, 1.f, 1.f});

	//Particles stars {sf::Color::White, 1, 2, sf::Vector2f{0.1,0.1}, sf::Vector2i{5, 10}, sf::Vector2f{mainWindow.getSize().x/2.f, mainWindow.getSize().y/2.f}, 400.f,
	//	sf::Vector2f{0.1f, 0.1f}, 80.f, sf::Vector2f{0.f, 360.f}
	//};

	 playerSize = 10.f;

	 player.setRadius(playerSize);
	 player.setPointCount(6);
	 player.setFillColor(Color(80,80,80,255));
	 player.setOrigin(vec2(playerSize,playerSize)*-1);
	 player.setPosition(200,200);

	 enemyColor = Color::White;

	/* sf::Music mainMusic;
	 mainMusic.openFromFile("LD26.ogg");
	 mainMusic.setVolume(50.f);
	 mainMusic.setLoop(true);
	 mainMusic.play();*/

	 fpsLimit = 200;

	 gameStatus = true;

	 // Menu init
	 gameMenu.titleText.setFont(mainFont);
	 gameMenu.titleText.setString("Triangle Super");
	 gameMenu.titleText.setCharacterSize(getSurface().getSize().y / 7);
	 gameMenu.titleText.setPosition(getSurface().getSize().x/2 - gameMenu.titleText.getGlobalBounds().width/2.f,
		 getSurface().getSize().y/2 - gameMenu.titleText.getGlobalBounds().height/2.f);

	 gameMenu.playText.setFont(mainFont);
	 gameMenu.playText.setString("Play!");
	 gameMenu.playText.setCharacterSize(getSurface().getSize().y / 15);
	 gameMenu.playText.setPosition(getSurface().getSize().x/3 - gameMenu.playText.getGlobalBounds().width/2.f,
		 (getSurface().getSize().y/3) *2 - gameMenu.playText.getGlobalBounds().height/2.f);

	 gameMenu.quitText.setFont(mainFont);
	 gameMenu.quitText.setString("Quit.");
	 gameMenu.quitText.setCharacterSize(getSurface().getSize().y / 15);
	 gameMenu.quitText.setPosition(getSurface().getSize().x/3 *2 - gameMenu.quitText.getGlobalBounds().width/2.f,
		 (getSurface().getSize().y/3)*2-gameMenu.quitText.getGlobalBounds().height/2.f);

	 gameMenu.scoreText.setFont(mainFont);
	 gameMenu.scoreText.setCharacterSize(getSurface().getSize().y / 15);
	 gameMenu.scoreText.setPosition(getSurface().getSize().x/2 - gameMenu.scoreText.getGlobalBounds().width/2.f,
		 (getSurface().getSize().y/3)-gameMenu.scoreText.getGlobalBounds().height/2.f);

#ifdef NEPHILIM_ANDROID
	 AndroidInterface::playMusic("LD26.ogg");
#endif

	 Log("Initialized Triangle Super. Window: (%d,%d)", getSurface().getSize().x, getSurface().getSize().y);

}

void SampleSprites::onEvent(Event &event)
{
	switch(event.type)
	{
	case Event::Closed:
		close();
		break;

	case Event::Resized:
		//mainView.setSize(vec2(mainEvent.size.width, mainEvent.size.height));
		//mainWindow.setView(mainView);
		break;

	case Event::TouchMoved:
		if(event.x > 0 && event.y > 0 &&
			static_cast<unsigned int>(event.x) < getSurface().getSize().x &&
			static_cast<unsigned int>(event.y) < getSurface().getSize().y)
			player.setPosition(event.x, event.y);
		break;
	case Event::MouseMoved:
		if(event.mouseMove.x > 0 && event.mouseMove.y > 0 &&
			static_cast<unsigned int>(event.mouseMove.x) < getSurface().getSize().x &&
			static_cast<unsigned int>(event.mouseMove.y) < getSurface().getSize().y)
			player.setPosition(event.mouseMove.x, event.mouseMove.y);
		break;


	case Event::TouchPressed:
		if(gameStatus)
		{
			if(gameMenu.playText.getGlobalBounds().contains(event.x, event.y))
			{
				gameStatus = false;
				Score = 0.f;
				scoreClock.reset();
				levelCounter = 0;
				level = 1;
				//mainMusic.stop();
				//mainMusic.play();
			}
			else if(gameMenu.quitText.getGlobalBounds().contains(event.x, event.y))
			{
				//mainMusic.stop();
				close();
			}
		}
		break;

	case Event::MouseButtonPressed:
		if(gameStatus)
		{
			if(gameMenu.playText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				gameStatus = false;
				Score = 0.f;
				scoreClock.reset();
				levelCounter = 0;
				level = 1;
				//mainMusic.stop();
				//mainMusic.play();
			}
			else if(gameMenu.quitText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				//mainMusic.stop();
				close();
			}
		}
		break;

	case Event::KeyPressed:
		if(event.key.code == Keyboard::Escape)
		{
			if(gameStatus){
				//mainWindow.close();
			}
			else
			{
				gameStatus = true;
				Enemies.clear();
				levelCounter = 0;
				level = 1;
				Score = 0.f;
			}
		}
		break;

	default:
		break;

	}
}

void SampleSprites::onUpdate(Time time)
{ 
	
}

void SampleSprites::onRender()
{
	getRenderer()->setClearColor(Color::Black);
	getRenderer()->setProjectionMatrix(mainView.getMatrix());

	if(gameStatus) // Main menu
	{
		
		//stars.Update();
		//getRenderer()->draw(stars.getSystem());
		getRenderer()->draw(player);
		getRenderer()->draw(gameMenu.titleText);
		getRenderer()->draw(gameMenu.playText);
		getRenderer()->draw(gameMenu.quitText);

		if(Score > 1.f)
		{
			String scoreString = String::number(Score);
			scoreString = scoreString.substr(0, scoreString.find('.')+3);
			gameMenu.scoreText.setString("Score: " + scoreString);
			getRenderer()->draw(gameMenu.scoreText);
			gameMenu.scoreText.setPosition(getSurface().getSize().x/2 - gameMenu.scoreText.getGlobalBounds().width/2.f,
				(getSurface().getSize().y/3)-gameMenu.scoreText.getGlobalBounds().height/2.f);
		}
	}
	else if(!gameStatus)
	{
		//Game
		if(levelClock.getElapsedTime().asMicroseconds()/1000.f > 1000.f/level)
		{
			int randomI = Math::randomInt(0, 8);
			levelClock.reset();
			Enemy::movementFunc func;

			if(randomI >= 4) func = sinMovement;
			else func = linearMovement;

			//auto AI = (randomInt >= 4 ? enemyAILine : enemyAISine);
			randomI %= 4;
			vec2 target = vec2(static_cast<float>(Math::randomInt(0.f, static_cast<float>(getSurface().getSize().x))), static_cast<float>(Math::randomInt(0.f, static_cast<float>(getSurface().getSize().y))) );
			vec2 source = (randomI < 2) ? ((randomI == 0) ? vec2(-20.f, static_cast<float>(Math::randomInt(0.f, static_cast<float>(getSurface().getSize().y)))) : vec2 (static_cast<float>(getSurface().getSize().x)+20.f, static_cast<float>(Math::randomInt(0.f, static_cast<float>(getSurface().getSize().y))))) : ((randomI == 3) ? vec2(static_cast<float>(Math::randomInt(0, static_cast<float>(getSurface().getSize().y))), -20.f) :
				vec2(static_cast<float>(Math::randomInt(0.f, static_cast<float>(getSurface().getSize().y))), static_cast<float>(getSurface().getSize().x)+20.f));
			
			Enemies.push_back(new Enemy(Color::White, source, target, func));
			levelCounter++;
			if(levelCounter > level * 10)
				level++;
		}

		incrementColor(enemyColor);

		for(unsigned int i = 0; i < Enemies.size(); ++i)
		{
			Enemies[i]->Update(gameClock.getElapsedTime().asMicroseconds()/1000.f);
			Enemies[i]->setColor(enemyColor);
			Enemies[i]->render(getRenderer());
			if(collides(Enemies[i]->getShape().getPosition(), player.getPosition()))
			{
				gameStatus = true;
				Enemies.clear();
				levelCounter = 0;
				Score = scoreClock.getElapsedTime().asMiliSeconds()*level/1000.f;
				level = 1;
				break;
			}
			if(Enemies[i]->getShape().getPosition().x > getSurface().getSize().x + 100 ||
				Enemies[i]->getShape().getPosition().x < -100 ||
				Enemies[i]->getShape().getPosition().y > getSurface().getSize().y + 100 ||
				Enemies[i]->getShape().getPosition().y < -100)
			{
				std::cout<<"Deleting enemy "<<i<<std::endl;
				Enemies.erase(Enemies.begin()+i);
			}
		}
		//stars.Update();
		//mainWindow.draw(stars.getSystem());
		String scoreString = String::number(scoreClock.getElapsedTime().asMiliSeconds()*level/1000.f);
		scoreString = scoreString.substr(0, scoreString.find('.')+3);

		textOverlay.setString(String("Level: ") + String::number(level) +
			String("\nScore: ")  + scoreString +
			String("\nEntities: ") + String::number(Enemies.size()));
		getRenderer()->draw(textOverlay);
		getRenderer()->draw(player);

	//	sf::sleep(sf::milliseconds((1.f/fpsLimit)*1000.f - gameClock.getElapsedTime().asMicroseconds()/1000.f));
		gameClock.reset();
	}
}
