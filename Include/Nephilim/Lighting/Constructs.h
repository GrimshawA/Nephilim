/*
	Let There Be Light
	Copyright (C) 2012 Eric Laukien

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgment in the product documentation would be
		appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CONSTRUCTS_H
#define CONSTRUCTS_H

#include <iostream>

namespace ltbl
{
	struct Color3f
	{
		float r, g, b;

		Color3f();
		Color3f(float R, float G, float B);
	};

	class Point2i
	{
	public:
		int x, y;

		Point2i(int X, int Y);
		Point2i();
	
		bool operator==(const Point2i &other) const;
	};

	class Vec2f 
	{
	public:
		float x, y;

		Vec2f();
		Vec2f(float X, float Y);

		bool operator==(const Vec2f &other) const;
		
		Vec2f operator*(float scale) const;
		Vec2f operator/(float scale) const;
		Vec2f operator+(const Vec2f &other) const;
		Vec2f operator-(const Vec2f &other) const;
		Vec2f operator-() const;
		
		const Vec2f &operator*=(float scale);
		const Vec2f &operator/=(float scale);
		const Vec2f &operator+=(const Vec2f &other);
		const Vec2f &operator-=(const Vec2f &other);
		
		float magnitude() const;
		float magnitudeSquared() const;
		Vec2f normalize() const;
		float dot(const Vec2f &other) const;
		float cross(const Vec2f &other) const;
	};

	class AABB
	{
	private:
		Vec2f center;
		Vec2f halfDims;

	public:
		Vec2f lowerBound;
		Vec2f upperBound;

		void CalculateHalfDims();
		void CalculateCenter();
		void CalculateBounds();

		// Constructor
		AABB();
		AABB(const Vec2f &bottomLeft, const Vec2f &topRight);

		// Accessors
		const Vec2f &GetCenter() const;

		Vec2f GetDims() const;

		const Vec2f &GetHalfDims() const;
		const Vec2f &GetLowerBound() const;
		const Vec2f &GetUpperBound() const;

		AABB GetRotatedAABB(float angleRads) const;

		// Modifiers
		void SetLowerBound(const Vec2f &newLowerBound);
		void SetUpperBound(const Vec2f &newUpperBound);
		void SetCenter(const Vec2f &newCenter);
		void IncCenter(const Vec2f &increment);

		void SetDims(const Vec2f &newDims);

		void SetHalfDims(const Vec2f &newDims);

		void SetRotatedAABB(float angleRads);

		// Utility
		bool Intersects(const AABB &other) const;
		bool Contains(const AABB &other) const;

		// Render the AABB for debugging purposes
		void DebugRender();

		friend class AABB;
	};
}

ltbl::Vec2f operator*(float scale, const ltbl::Vec2f &v);
std::ostream &operator<<(std::ostream &output, const ltbl::Vec2f &v);

#endif