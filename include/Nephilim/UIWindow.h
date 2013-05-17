#ifndef NephilimUIWindow_h__
#define NephilimUIWindow_h__

#include "Platform.h"
#include "Event.h"
#include "Renderer.h"
#include "Drawable.h"

#include "UIControl.h"
#include "UIState.h"
#include "UISurface.h"
#include "UIToolTip.h"


NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UIWindow
	\brief A Surface to draw user interface controls.

	This class is a drawable and therefore can be rendered directly with Renderer::draw()
	It works as a graphical object that contains user interface controls (widgets).

	Its dimensions start at the origin (0,0) and end at (width,height)
*/
class NEPHILIM_API UIWindow : public Drawable
{
public:
	/// Construct the window
	UIWindow();

	/// Returns a control in the hierarchy with the name, or NULL if not found
	UIControl* getControlByName(const String& name);

	/// Drawable rendering
	void onDraw(Renderer* renderer);

	/// Sets new boundaries to this UIWindow
	void setRect(Rect<float> rect);

	/// Get the position of the exact middle of this UIWindow
	Vec2f getMiddlePosition();

	/// Set the current language of the ui system
	void setLanguage(const String& shortLanguageName);

	/// Creates a new surface, which is underneath the relativeSurface specified
	/// \return NULL in case the relativeSurface is not a valid surface
	UISurface* createSurfaceBelow(UISurface* relativeSurface, const String& name);

	/// Get a surface by its name
	UISurface* getSurfaceByName(const String& name);

	/// Get the surface closer to the user
	/// \return the UISurface* or NULL if there are no surfaces
	UISurface* getTopSurface();

	UISurface* addSurface(const String& name);

	void applyPendingChanges();

	typedef std::vector<UIControl*> ControlList;

	/// Makes a list of controls from a selector - CSS like
	ControlList selectControls(const String& selector);

	void showMessageBox(const String& message);

	UIStateContext& getContext();

	/// Draw the UI
	void draw(Renderer* renderer);

	/// Update the state of the ui
	void update(float elapsedTime);
	
	/// Pushes a new event through the ui system
	bool pushEvent(Event& event);

	/// Process a mouve movement event
	/// Returns false if the mouse isnt on any control
	bool processMouseMove(int x, int y);

	/// Process a mouse press event
	bool processMouseButtonPressed(int x, int y, Mouse::Button button);

	/// Destroys all surfaces without children
	void clearUnusedSurfaces();

	/// Get the current surface count
	int getSurfaceCount();

	/// Get a surface by its name. It will be created if it does not yet exist
	UISurface* operator[](const String& name);

	/// Get a surface directly by its index
	/// You must ensure that index is valid
	UISurface* operator[](unsigned int index);


	Color m_topBorderColor, m_bottomBorderColor, m_leftBorderColor, m_rightBorderColor;
	Color m_backgroundColor;
private:
	/// The bounds of the window
	/// In nearly every case, the bounds match exactly the dimensions of the screen
	/// But for particular reasons, the working area of the user interface system can be smaller or bigger.
	Rect<float> m_bounds;

	/// Multiple layers in the interface controls
	/// m_surfaces[0] is the top layer, the closer to the user
	std::vector<UISurface*> m_surfaces;

	/// The shared state of this ui system
	UIStateContext m_state;

	/// Tooltips
	UIToolTip* m_toolTip;
	bool m_showingToolTip;
	float m_timeSinceLastMouseMovement;

	enum PendingChangeType
	{
		Add,
		Remove,
		Reorder,
		Clear
	};

	typedef struct{
		PendingChangeType type;
		UISurface* surface;
	} PendingChange;

	std::vector<PendingChange> m_pendingChanges;

	bool m_surfaceContainerLock;
};

NEPHILIM_NS_END
#endif // NephilimUIWindow_h__