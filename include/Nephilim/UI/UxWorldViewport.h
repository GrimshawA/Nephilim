#ifndef UxWorldViewport_h__
#define UxWorldViewport_h__

#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

class World;

/**
	\class UxWorldViewport
	\brief Widget to render a World's frame
*/
class NEPHILIM_API UxWorldViewport : public Widget
{
public:
	/// The world we are rendering
	World* _world = nullptr;

public:

	UxWorldViewport(World* worldPtr);

	/// Get the object name of this node
	virtual const char* getName();

	/// Get the class name of this node
	virtual const char* getClassName();

	/// Render the node
	virtual void render(GraphicsDevice* gdi);
};

NEPHILIM_NS_END
#endif // UxWorldViewport_h__
