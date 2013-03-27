#ifndef PARABOLA_BOUNDINGBOX_H
#define PARABOLA_BOUNDINGBOX_H

#include "Platform.h"
#include "Vectors.h"

PARABOLA_NAMESPACE_BEGIN

	/**
		\ingroup Foundation
		\class BoundingBox
		\brief Represents an axis aligned box (no rotations)


		
	*/
	class PARABOLA_API BoundingBox{
	public:
		/// Creates a default (0,0)(0,0) rectangle
		BoundingBox();

		/// Creates a rectangle from the coordinates
		BoundingBox(float left, float top, float width, float height);

		/// Checks if a point is within the box
		bool contains(float x, float y);

		/// Sets the rect at once
		void set(float left, float top, float width, float height);

		/// Move the box relative to its position
		void move(float x, float y);

		/// Set the box position
		void setPosition(float x, float y);

		/// Check if there is intersection between two bounding boxes
		bool intersects(BoundingBox &box);

		/// Top-left position of this box
		Vec2f Position;
		/// Width and Height of this box
		Vec2f Size;
	};

	typedef BoundingBox AABB;

PARABOLA_NAMESPACE_END
#endif