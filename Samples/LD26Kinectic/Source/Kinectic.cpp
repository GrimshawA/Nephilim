#include "Kinectic.h"

#include <Nephilim/CGL.h>
#include <Nephilim/Image.h>

#include <Nephilim/KxScene.h>
#include <Nephilim/KxDraw.h>
#include <Nephilim/KxMousePicker.h>
#include <Nephilim/KxRope.h>


#include <Nephilim/DateTime.h>

#include <Nephilim/ParticleSystem.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/MMath.h>

#include <iostream>
using namespace std;

KxScene world;

Texture tex;

ParticleSystem p1;

std::vector<KxBody*> actors;
std::vector<ParticleSystem> actorParticles;

float angle = 0; 
float angleInc = Math::pi*2 / 4;
float torusRadius = 30;

float p = 2;
float q = 3;

vec2 pointA = vec2(10,10);
vec2 pointB = vec2(500,500);
vec2 curr_position = pointA;
vec2 curr_linear_position = pointA;
float speed = 50;
float frequency = 2;

KxMousePicker picker;

void Kinectic::onCreate()
{	
	Log("hello %d %d %d", 20, 30, 40);

	world.CreateQuickCircle(200,200,20);
	world.CreateStaticBox(0,600,2500, 10);

	world.setPositionIterations(20);
	world.setVelocityIterations(20);

	KxRopeBuilder rope;
	rope.sim = &world;
	rope.createRope(vec2(100,100), 30, 4);
	rope.createRope(vec2(200,100), 6, 15);
	rope.createRope(vec2(300,100), 6, 20);
	rope.createRope(vec2(400,100), 6, 25);
	rope.createRope(vec2(500,100), 2, 30);
	rope.createRope(vec2(600,100), 6, 35);
	rope.createBridge(vec2(100,400), vec2(600,400), 30);

	tex.loadFromFile("as2.png");

	picker.scene = &world;

	p1.create();
	p1.tank = 2;
	p1.position = vec3(200,200,0);
}

void Kinectic::onEvent(Event &event)
{
	if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		picker.attachAt(event.mouseButton.x, event.mouseButton.y);
	}
	if(event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		picker.detach();
	}
	if(event.type == Event::MouseMoved)
	{
		picker.update(event.mouseMove.x, event.mouseMove.y);
	}

   if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::XButton1)
   {
	   world.CreateQuickCircle(event.mouseButton.x,event.mouseButton.y,20);
   }

   if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
   {
	   KxBody* actor = world.CreateQuickBox(event.mouseButton.x,event.mouseButton.y, 20, 20);
	   actors.push_back(actor);
	   ParticleSystem pp;
	   pp.create();
	   pp.tank = 35;
	   actorParticles.push_back(pp);
	   cout << "box position: "<<actor->m_body->GetPosition().y * 100<<endl;
   }

   if(event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
   {
	   p++;cout << "p: "<< p << " q: "<<q<<endl;
   }
   if(event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
   {
	   p--;cout << "p: "<< p << " q: "<<q<<endl;
   }
   if(event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
   {
	   q++;cout << "p: "<< p << " q: "<<q<<endl;
   }
   if(event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
   {
	   q--; cout << "p: "<< p << " q: "<<q<<endl;
   }
   if(event.type == Event::KeyPressed && event.key.code == Keyboard::F1)
   {	 
	  Image image;
	  getRenderer()->readPixels(image);
	  String path = "screenshot" + DateTime::timeStamp() + ".png";
	  image.saveToFile(path);
	   cout << "Screenshot taken: " << path << endl;
   }
}

void Kinectic::onUpdate(Time time)
{ 
	world.update(time.asSeconds());

	for(int i =0; i < actors.size(); i++)
	{
		//cout << "box position: "<<actors[i]->getPosition().y<<endl;
		actorParticles[i].position = vec3(actors[i]->getPosition(), 0);
		actorParticles[i].update(time.asSeconds());
	}

	angle += angleInc * time.asSeconds();

	float r = cos(q * angle) + 2;
	p1.position = vec3(300 + r * cos(p * angle) * torusRadius, 300 + r * sin(p * angle) * torusRadius, 0);
	// override
	static float traveled = 0;

	vec2 direction = pointB - curr_linear_position; direction.normalize();
	float sin_deviation = sin(frequency * angle) - 0.5;
	vec2 deviation = vec2(-direction.y, direction.x); 
	deviation *= sin_deviation * 30;
	curr_linear_position += direction * speed * time.asSeconds();
	curr_position = curr_linear_position + deviation;

	p1.position = vec3(curr_position, 0);
	p1.update(time.asSeconds());
}

void Kinectic::onRender()
{
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(View(0,0,1024,768).getMatrix());


	Sprite s;
	s.setTexture(tex);
	s.resize(1024,768);
	getRenderer()->draw(s);

	getRenderer()->draw(KxDraw(world));

	for(int i =0; i < actors.size(); i++)
	{
		getRenderer()->draw(actorParticles[i]);
	}

	getRenderer()->draw(p1);
}
