#include "Enemy.h"

void Enemy::setColor(Color color)
{
	shape.setFillColor(color);
	color.r -= 60;
	color.g -= 60;
	color.b -= 60;
//	particleSystem.setColor(color);
}


const CircleShape &Enemy::getShape()
{
	return shape;
}


void Enemy::Update(float delaTime)
{
	shape.setPosition(algorithm(shape.getPosition(), startingPoint, Destination, linearPosition, angle, delaTime));
	//particleSystem.setPosition(shape.getPosition());
	//particleSystem.Update();
}

void Enemy::render(Renderer* renderer)
{
	//window.draw(particleSystem.getSystem());
	renderer->draw(shape);
}

Enemy::Enemy(Color color, vec2 position, vec2 Destination_, movementFunc algorithm_) /*:
particleSystem(sf::Color(color.r-100, color.b-100, color.g-100, color.a), 4, 10, sf::Vector2f(0.5f,0.5f), sf::Vector2i(0,3),
	position, 5.f, sf::Vector2f(5.f,5.f), 5.f, sf::Vector2f(0.f, 360.f))*/
{
	Destination = Destination_;
	algorithm = algorithm_;
	startingPoint = position;
	linearPosition = position;
	shape.setPointCount(15);
	//shape.setPoint(0, sf::Vector2f(0,0));
	//shape.setPoint(1, sf::Vector2f(10,5));
	//shape.setPoint(2, sf::Vector2f(20,0));
	//shape.setPoint(3, sf::Vector2f(10,15));
	shape.setFillColor(color);
	shape.setOrigin(10,5);
	shape.setPosition(position);
	shape.setRadius(10); //new
	shape.setOrigin(-10, -10); // new
	vec2 direction = Destination - position;
	direction.normalize();
	(direction.x > 0) ? (shape.rotate(std::atan(direction.y / direction.x) * 180 / Math::pi - 90)) : (shape.rotate(std::atan(direction.y / direction.x) * 180 / Math::pi - 270));
}