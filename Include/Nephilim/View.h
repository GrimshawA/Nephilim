#ifndef PARABOLA_VIEWS_H
#define PARABOLA_VIEWS_H

#include "Platform.h"
#include "Vectors.h"
#include "Rect.h"
#include "Transform.h"
#include "ReferenceCountable.h"

PARABOLA_NAMESPACE_BEGIN

enum ViewportPreset{
	TopLeftQuarter = 0,
	TopRightQuarter,
	BottomLeftQuarter,
	BottomRightQuarter,
	LeftHalf,
	RightHalf,
	TopHalf,
	BottomHalf,
	WideScreen
};

/**
		\ingroup Graphics
		\class View
		\brief Represents a 2D camera

		In practice, it is a 2D projection of your scene, orthogonal, which you can configure to taste.
*/
class PARABOLA_API View : public RefCountable{
public:
		View();

		/// Set the view center as a position
		void setCenter(Vec2f position);

		/// Set the view center as a position
		void setCenter(float x, float y);

		/// Set the viewport
		/// This helps define the usable render area of the screen
		void setViewport(FloatRect viewport);

		FloatRect getViewport() const;

		/// Set the viewport from one of the presets
		void setViewportPreset(int preset);

		/// Get the dimensions of the view rect
		Vec2f getSize();

		/// Set the size of the view rect, perserving its center
		void setSize(float width, float height);

		void move(float x, float y);

		/// Zoom the view by a factor
		void zoom(float factor);

		/// Rotate the view by the given degree angle
		void rotate(float degrees);

		/// Get the view center
		Vec2f getCenter();

		FloatRect getRect() const;

		/// Reset the view to this rect
		void setRect(float x, float y, float width, float height);

		const Transform& getInverseTransform() const;
		const Transform& getTransform() const;

    
    float m_rotation;
private:
	FloatRect m_rect;
	FloatRect m_viewport;
	mutable Transform m_transform;
	mutable Transform m_inverseTransform;
	
	mutable bool m_transformUpdated;
	mutable bool m_invTransformUpdated;
	mutable Vec2f m_center;

};
	
/// Typedef of View to Camera2D to suit tastes
typedef View Camera2D;


// AngelScript registration
class ASEngine;
bool registerView(ASEngine* engine);

PARABOLA_NAMESPACE_END

#endif