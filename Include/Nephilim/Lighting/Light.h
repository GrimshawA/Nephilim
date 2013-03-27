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

#ifndef LIGHT_H
#define LIGHT_H

#include "SFML_OpenGL.h"
#include "Constructs.h"
#include "QuadTree.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace ltbl
{
	const float lightSubdivisionSize = static_cast<float>(M_PI) / 24.0f;

	class LightSystem;

	class Light :
		public qdt::QuadTreeOccupant
	{
	private:
		int numSubdivisions;

		sf::RenderTexture* pStaticTexture;

		bool alwaysUpdate;

		sf::RenderWindow* pWin;

		// Set up viewport information for the render texture
		void SwitchStaticTexture();

		bool updateRequired;

	public:
		float radius;
		Vec2f center;
		float directionAngle;
		float spreadAngle;

		float intensity;
		
		float size;
		
		float softSpreadAngle;

		Color3f color;

		Light();
		~Light();

		void SetRadius(float Radius);
		void IncRadius(float increment);
		float GetRadius();

		void SetCenter(Vec2f Center);
		void IncCenter(Vec2f increment);
		Vec2f GetCenter();

		void SetDirectionAngle(float DirectionAngle);
		void IncDirectionAngle(float increment);
		float GetDirectionAngle();

		void SetSpreadAngle(float SpreadAngle);
		void IncSpreadAngle(float increment);
		float GetSpreadAngle();

		virtual void RenderLightSolidPortion(float depth);
		virtual void RenderLightSoftPortion(float depth);
		virtual void CalculateAABB();
		AABB* GetAABB();

		bool AlwaysUpdate();
		void SetAlwaysUpdate(bool always);

		friend LightSystem;
	};
}

#endif