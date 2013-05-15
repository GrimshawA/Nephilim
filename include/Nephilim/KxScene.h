#ifndef KinesisWorld_h__
#define KinesisWorld_h__

#include "Platform.h"
#include "Vectors.h"

#include "KxBody.h"

class b2World;

NEPHILIM_NS_BEGIN
	
/**
	\ingroup Kinesis
	\class KxScene
	\brief Provides a complete physics simulation, powered by Box2D.
*/
class KxScene{
public:		
	/// Constructs the world with default settings. Gravity pulls towards Y+
	KxScene();

	/// Constructs the world with initial settings
	KxScene(Vec2f gravity, int velocityIterations = 6, int positionIterations = 6);

	/// Destroy the box2d world
	~KxScene();
		
	/// Get the number of pixels in a meter.		
	float getPixelRatio();
			
	/// Update the simulation
	void update(float elapsedTime);

	/// Get the raw b2World object
	b2World* get();

	/**
		\brief Set the Velocity iteration count
	*/
	void setVelocityIterations(int velocityIterations);
	/**
		\brief Get the Velocity iteration count
	*/
	int getVelocityIterations();
	/**
		\brief Set the Position iteration count
	*/
	void setPositionIterations(int positionIterations);
	/**
		\brief Sets the Position iteration count
	*/
	int getPositionIterations();

	float toMeters(float amount);
	float toPixels(float amount);

	b2Body* getGroundBody();
	b2Body* createDefaultGroundBody();

	b2Body* CreateQuickCircle(float x, float y, float r);
	KxBody* CreateQuickBox(float x, float y, float width, float height);
	void CreateQuickLine(float x, float y, float xx, float yy);
	b2Body* CreateStaticBox(float x, float y, float width, float height);
	
private:
	int m_velocityIterations; ///< Velocity iteration count
	int m_positionIterations; ///< Position iteration count

	/// Amount of pixels in a meter
	float m_pixelsPerMeter;

	b2MouseJoint* pickerMouseJoint;
	b2Body* defaultGroundBody;

	b2World* m_world;	///< Box2D World
};

NEPHILIM_NS_END
#endif // KinesisWorld_h__
