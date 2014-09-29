#ifndef KinesisDebugDraw_h__
#define KinesisDebugDraw_h__

#include <Nephilim/Platform.h>
#include "Drawable.h"

NEPHILIM_NS_BEGIN

class KxScene;

/**
	\ingroup Kinesis
	\class KxDraw 
	\brief This drawable can draw debug data of a Kinesis (KxScene) simulation
*/
class NEPHILIM_API KxDraw : public Drawable
{
public:
	/// Initialize with no scene
	KxDraw();

	/// Initialize with a scene
	KxDraw(KxScene& scene);

	/// Set the scene to be drawn
	void setScene(KxScene& scene);

	/// Get the scene assigned to this instance
	KxScene* getScene();

	/// Draw the debug data of KxScene
	void onDraw(GraphicsDevice* renderer);

private:
	float m_pixelsPerMeter;
	KxScene* m_scene;
};

NEPHILIM_NS_END

#endif // KinesisDebugDraw_h__
