#include <Nephilim/CollisionData.h>

NEPHILIM_NS_BEGIN

/// Add a new body to the collection
CollisionData::Body& CollisionData::addBody()
{
	mBodies.push_back(Body());
	return mBodies.back();
}

void CollisionData::Body::addRect(float center_x, float center_y, float width, float height)
{
	CollisionData::Shape s;
	s.position.x = center_x;
	s.position.y = center_y;
	s.size.x = width;
	s.size.y = height;
	mShapes.push_back(s);
}

NEPHILIM_NS_END