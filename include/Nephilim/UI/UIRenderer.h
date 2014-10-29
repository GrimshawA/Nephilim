#ifndef NephilimUIRenderer_h__
#define NephilimUIRenderer_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

/**
	\class UIRenderer
	\brief Base class for UI renderers

	The UIRenderer goes through the UI hierarchy and renders it to the screen.
	As it traverses the hierarchy, the views will handle back the geometry and used textures
	to be rendered, but the renderer itself has all power over what to render and how to render it.
*/
class UIRenderer
{
public:

};


/*
	\class UIDefaultRenderer
	\brief Default UI renderer

	In most cases this is all that is needed, only write a custom UI renderer
	if you absolutely need to.
*/
class UIDefaultRenderer : public UIRenderer
{
public:

};

NEPHILIM_NS_END
#endif // NephilimUIRenderer_h__
