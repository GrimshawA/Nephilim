#ifndef KinesisWorld_h__
#define KinesisWorld_h__

#include "Platform.h"
#include "Vectors.h"

#include "KinesisActors.h"

class b2World;

NEPHILIM_NS_BEGIN

class Renderer;
	
/**
	\ingroup Kinesis
	\class KinesisWorld
	\brief Provides a complete physics simulation, powered by Box2D.

	You may use this class to create rich physics simulations.

*/
class KinesisWorld{
public:		
	/// Constructs the world with default settings. Gravity pulls towards Y+
	KinesisWorld();

	/// Constructs the world with initial settings
	KinesisWorld(Vec2f gravity, int velocityIterations = 6, int positionIterations = 6);
		
	/// Get the number of pixels in a meter.		
	float getPixelRatio();
			
	/// Update the simulation
	void update(float elapsedTime);

	/// Get the raw b2World object
	b2World* get();

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


	private:
		int m_velocityIterations, m_positionIterations;

		/// Amount of pixels in a meter
		float m_pixelsPerMeter;

		b2MouseJoint* pickerMouseJoint;
		b2Body* defaultGroundBody;
		
		//friend class SceneRenderer;

		b2World* m_world;	///< Box2D World
	};

NEPHILIM_NS_END
#endif // KinesisWorld_h__
