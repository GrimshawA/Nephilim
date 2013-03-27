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

#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "SFML_OpenGL.h"
#include "Constructs.h"
#include "QuadTree.h"
#include <vector>

namespace ltbl
{
	template<class T> T Wrap(T val, T size)
	{
		if(val < 0)
			return val + size;

		if(val >= size)
			return val - size;

		return val;
	}

	struct ConvexHullVertex
	{
		Vec2f position;

		// Other information can be added later
	};

	class ConvexHull :
		public qdt::QuadTreeOccupant
	{	
	private:
		bool aabbGenerated;

		Vec2f worldCenter;

		bool updateRequired;

		bool render;

		std::vector<Vec2f> normals;

	public:
		std::vector<ConvexHullVertex> vertices;

		ConvexHull();

		void CenterHull();
		bool LoadShape(const char* fileName);
		Vec2f GetWorldVertex(unsigned int index) const;

		void CalculateNormals();

		void RenderHull(float depth);

		void GenerateAABB();

		bool HasGeneratedAABB();

		void SetWorldCenter(const Vec2f &newCenter);
		void IncWorldCenter(const Vec2f &increment);

		Vec2f GetWorldCenter() const;

		bool PointInsideHull(const Vec2f &point);
		
		friend class LightSystem;
	};

	float GetFloatVal(std::string strConvert);
}

#endif

