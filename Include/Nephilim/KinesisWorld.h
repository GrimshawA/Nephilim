#ifndef PARABOLA_KINESISWORLD_H
#define PARABOLA_KINESISWORLD_H

#include "Platform.h"
#include "Strings.h"
#include <Box2D/Box2D.h>
#include "Vectors.h"
#include "KinesisDebugDraw.h"
#include "KinesisActors.h"

//#include "KinesisForge.h"
//#include "KinesisContactListener.h"
//#include "KinesisQueryCallback.h"

PARABOLA_NAMESPACE_BEGIN
class Renderer;
	
/**
	\ingroup Kinesis
	\class KinesisWorld
	\brief Provides a complete physics simulation, powered by Box2D.

	You may use this class to create rich physics simulations.

*/
class KinesisWorld : public b2World{
public:		
	/// Constructs the world with normal gravity (0, 0,98), scaled for optimal performance.
	KinesisWorld();

	/// Constructs the world with the given settings		
	KinesisWorld(Vec2f gravityForce);
		
	/// Get the number of pixels in a meter.		
	float getPixelRatio();

	/// Draw the simulation in test mode through a renderer
	void drawDebugShapes(Renderer* renderer);
			
	/// Update the simulation
	void update(float elapsedTime);

	/// Destroy a body by its actor
//	void destroyBodyActor(KinesisBodyActor *actor);


		/**
			\brief Set the Velocity iteration count
		*/
		void SetVelocityIterationCount(int velocityIterations);
		/**
			\brief Get the Velocity iteration count
		*/
		int GetVelocityIterationCount();
		/**
			\brief Set the Position iteration count
		*/
		void SetPositionIterationCount(int positionIterations);
		/**
			\brief Sets the Position iteration count
		*/
		int GetPositionIterationCount();



		float ToMeters(float amount);
		float ToPixels(float amount);

		b2Body* GetGroundBody();
		b2Body* CreateDefaultGroundBody();

		/**
			\brief Picking
		*/
		bool StartPicking(float x, float y);
		void StopPicking();
		bool IsPickingEnabled();
		void UpdatePicking(float x, float y);

		b2Body* CreateQuickCircle(float x, float y, float r);
		KinesisBodyActor* CreateQuickBox(float x, float y, float width, float height);
		void CreateQuickLine(float x, float y, float xx, float yy);
		b2Body* CreateStaticBox(float x, float y, float width, float height);


	

		/**
			\brief Loads objects from FileName and adds them to this simulation

			Creates a World Definition object and loads the custom text file with it, making changes in this KinesisWorld
		*/
		bool LoadFromFile(String FileName);



		/**
			\brief d
		*/
		//KinesisDebugDraw* GetDebugRenderer();
		

	private:
		int VelocityIterations, PositionIterations;

		/// Amount of pixels in a meter
		float myPixelRatio;
		
		KinesisDebugDraw myDebugDraw;

		//KinesisContactListener contactListener;
//		mutable sf::Mutex mutex;

		b2MouseJoint* pickerMouseJoint;
		b2Body* defaultGroundBody;
		
		//friend class SceneRenderer;
		
	};

PARABOLA_NAMESPACE_END
#endif