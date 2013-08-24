#ifndef NephilimUIDocument_h__
#define NephilimUIDocument_h__

#include "Platform.h"
#include "Drawable.h"
#include "Event.h"
#include "UICore.h"

NEPHILIM_NS_BEGIN

class Renderer;
class UISurface;
class UIControl;

/**
	\ingroup UI
	\class UIDocument
	\brief A Surface to draw user interface controls.

	This class is a drawable and therefore can be rendered directly with Renderer::draw()
	It works as a graphical object that contains user interface controls (widgets).

	When you render a UIDocument you are drawing a rectangle with the chosen dimensions in the plane z=0,
	which includes all controls within that rectangle.
*/
class NEPHILIM_API UIDocument : public Drawable
{
public:
	/// Construct the window
	UIDocument();

	/// Returns a control in the hierarchy with the name, or NULL if not found
	UIControl* getControlByName(const String& name);

	/// Drawable rendering
	void onDraw(Renderer* renderer);

	/// Set new boundaries for this document
	/// Note: It is preferred that this rect is in absolute coordinates in the same coordinate system as the mouse coordinates passed in
	void setRect(Rect<float> rect);

	/// Set the new boundaries for this document
	void setRect(float left, float top, float width, float height);

	/// Get the position of the exact middle of this UIWindow
	Vec2f getMiddlePosition();

	/// Set the current language of the ui system
	void setLanguage(const String& shortLanguageName);

	/// Get a surface by its name
	UISurface* getSurfaceByName(const String& name);

	/// Get the count of modal surfaces
	int getModalSurfaceCount();

	/// Get the surface closer to the user
	/// \return the UISurface* or NULL if there are no surfaces
	UISurface* top();

	/// Push a new modal surface to the top, it will destroy itself once there are no more controls in it
	void pushModalSurface();

	UISurface* addSurface(const String& name);

	/// Destroys a surface from its children
	void destroySurface(UISurface* surface);

	void applyPendingChanges();

	typedef std::vector<UIControl*> ControlList;

	/// Makes a list of controls from a selector - CSS like
	ControlList selectControls(const String& selector);

	void showMessageBox(const String& message);

	UICore& getContext();

	/// Draw the UI
	void draw(Renderer* renderer);

	/// Update the state of the ui
	void update(float elapsedTime);
	
	/// Pushes a new event through the ui system
	UIEventResult pushEvent(const Event& event);

	/// Process a mouve movement event
	/// Returns false if the mouse isnt on any control
	bool processMouseMove(int x, int y);

	void processTouchMove(int x, int y);

	/// Process a mouse press event
	bool processMouseButtonPressed(int x, int y, Mouse::Button button);

	/// Process a mouse release event
	void processMouseButtonReleased(int x, int y, Mouse::Button button, UIEventResult& info);

	/// Destroys all surfaces without children
	void clearUnusedSurfaces();

	/// Get the current surface count
	int getSurfaceCount();

	//debug
	void debugData();

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
	UICore m_state;

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

	int m_surfaceContainerLock;
};

NEPHILIM_NS_END
#endif // NephilimUIDocument_h__