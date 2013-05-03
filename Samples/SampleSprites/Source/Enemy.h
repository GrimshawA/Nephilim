#ifndef Enemy_h__
#define Enemy_h__

#include <Nephilim/Vectors.h>
#include <Nephilim/Color.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/MMath.h>
#include <Nephilim/CircleShape.h>
//#include <Thor/Graphics.hpp>
//#include <Thor/Shapes.hpp>
//#include <Thor/Particles.hpp>
//#include <Thor/Math.hpp>
//#include <SFML/Graphics.hpp>
//#include "Particles.hpp"
#include <cmath>

using namespace nx;

class Enemy
{
public:
	//Particles particleSystem;
	CircleShape shape;
	vec2 Destination, linearPosition, startingPoint;
	float angle;

	typedef vec2 (*movementFunc)(vec2, vec2&, vec2&, vec2&, float&, float);
	movementFunc algorithm;

public:
	void incrementColor();
	void setColor(Color color);
	const CircleShape &getShape();
	void Update(float delaTime);
	void render(Renderer* renderer);
	Enemy(Color color, vec2 position, vec2 Destination_, movementFunc algorithm_);
};

#endif // Enemy_h__
