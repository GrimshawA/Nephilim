#ifndef PARABOLA_SCENERENDERER_H
#define PARABOLA_SCENERENDERER_H

#include "Platform.h"
#include "SFML/Graphics.hpp"
#include "LinkedPointer.h"
#include "Strings.h"
#include "Drawable.h"
#include "Window.h"
#include "Vectors.h"
#include "Views.h"

PARABOLA_NAMESPACE_BEGIN
	class SceneGraph;
	class RocketContext;
	
	typedef sf::RenderTarget RenderTarget;
	typedef sf::RenderStates RenderStates;

/**
	\ingroup Graphics
	\class SceneRenderer
	\brief Responsible to draw everything in the scene

		Renderers need to point to a RenderTarget in order to be able to draw anything.

		A RenderTarget can be a window, a texture,etc and it will be completely transparent
		to draw to one or another.

		For ultimate flexibility, you will be able to stuff all your scene in a SceneGraph
		and draw the whole thing with one call. 

		By doing this, you could even draw your scene to multiple windows and/or textures,
		just by reassigning targets and redrawing the graph.

		Rendering process will be split into two ways:
			- Component based SceneGraph (Entities with a GraphicsComponent)
			- Loose graphic objects (such as Text,Sprite,etc)

		Both ways are very useful and can be mixed together.
		Also, using one or the other depends on how you decide 
		to design your game. The most simple games should be really
		fine with holding graphic objects the old traditional way,
		while complex scenes would certainly take advantage of
		using SceneGraph structures.

*/
class PARABOLA_API SceneRenderer{
public:
		/// Creates a renderer with no render target
		SceneRenderer();
		/// Creates a renderer bound to [target]
		SceneRenderer(RenderTarget &target);

		/// Returns the bound render target or NULL if none is assigned
		RenderTarget* getRenderTarget();

		/// Binds the target to the renderer
		void setRenderTarget(RenderTarget &target);

		/// Get the size of the target
		Vec2i getTargetSize();

		/// Get the size of the window
		Vec2i getWindowSize();

		/// Draw a text in the screen
		void drawDebugText(const String &text, float x, float y);

		/// Draws a debug circle
		void drawDebugCircle(float x, float y, float r);

		/// Activate the window
		void activateRenderTarget();

		/// Convert local coordinates to global ones from the current view
		Vec2f convertLocalCoordinates(Vec2f localCoordinates);

		/// Convert local coordinates to global ones from a view
		Vec2f convertLocalCoordinates(Vec2f localCoordinates, View& v);


		/// Assign the view to the target directly
		void setView(const View &view);

		/// Get the currently applied view
		const View& getView();

		/// Sets the center of the view - the eye
		/// in world coordinates
		void setViewEye(Vec2f position);

		/// Rotates the view by [angle]
		/// In degrees
		void setViewRotation(float angle);

		/// Draws any SFML drawable or any inherited drawable into the target
		void draw(Drawable &drawable);

		/// Draws a rocket context
		void draw(RocketContext *rContext);

		/// Draws recursively a SceneGraph
		/// The graph can contain your whole scene of objects and entities
		/// Not all nodes need to have rendering behaviors
		void draw(SceneGraph &scene);

		/// Draws a SFML inherited drawable into a different target
		/// Use keepView to determine if the target will be used with the current target view
		void drawAt(RenderTarget &target, Drawable &drawable, bool keepView);

private:
	RenderTarget* myTarget;
	Window* myWindow;
	std::vector<View*> myViewStack;
};

	
	

PARABOLA_NAMESPACE_END
#endif