#include "Nephilim/BoundingBox.h"

NEPHILIM_NS_BEGIN

BoundingBox::BoundingBox(){
		Position.x = Position.y = Size.x = Size.y = 0.f;
}

BoundingBox::BoundingBox(float left, float top, float width, float height){
		Position.x = left;
		Position.y = top;
		Size.x = width;
		Size.y = height;
}

/// Checks 
bool BoundingBox::contains(float x, float y){
		return(x >= Position.x &&
		   x <= Position.x + Size.x &&
		   y >= Position.y &&
		   y <= Position.y + Size.y );
};

void BoundingBox::set(float left, float top, float width, float height){
	Position.x = left;
	Position.y = top;
	Size.x = width;
	Size.y = height;
};

void BoundingBox::move(float x, float y){
	Position.x += x;
	Position.y += y;	
};

/// Set the box position
void BoundingBox::setPosition(float x, float y){
	Position.x = x;
	Position.y = y;	
};

/// Check if there is intersection between two bounding boxes
bool BoundingBox::intersects(BoundingBox &box){
	return (box.contains(Position.x, Position.y) ||
			box.contains(Position.x, Position.y + Size.y) ||
			box.contains(Position.x + Size.x, Position.y) ||
			box.contains(Position.x + Size.x, Position.y + Size.y) );
};

NEPHILIM_NS_END