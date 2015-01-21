#ifndef NephilimUICanvas_h__
#define NephilimUICanvas_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/Drawable.h>
#include <Nephilim/Foundation/Event.h>
#include <Nephilim/UI/UICore.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class UIWindow;
class UIView;

/**
	\ingroup UI
	\class UICanvas
	\brief Container for UI elements

	A UICanvas is an object that represents a rectangle of any dimension in which child UI elements are rendered to.
*/
class NEPHILIM_API UICanvas : public Drawable
{
public:

	/// The name of this canvas
	String m_name;

public:

	/// Construct the window
	UICanvas();

	/// Create a window for this canvas
	UIWindow* createWindow(const String& name);

	/// Load a stylesheet file into the canvas
	bool loadStylesheet(const String& filename);

	/// Update the window size of the UI canvas
	/// This will effectively change the size of all subwindows to match the new canvas size, if they are fullscreen
	void setWindowSize(int w, int h);

	/// Returns a control in the hierarchy with the name, or NULL if not found
	UIView* getControlByName(const String& name);

	/// Adds a layer to this canvas for 2D controls
	void addLayer2D(const String& name);

	/// Adds a layer to this canvas for 3D controls
	void addLayer3D(const String& name);

	/// Drawable rendering
	void onDraw(GraphicsDevice* renderer);

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
	UIWindow* getLayer(const String& name);

	/// Get the count of modal surfaces
	int getModalSurfaceCount();

	/// Get the surface closer to the user
	/// \return the UISurface* or NULL if there are no surfaces
	UIWindow* top();

	/// Print hierarchy information for debugging
	void printHierarchy();

	/// Push a new modal surface to the top, it will destroy itself once there are no more controls in it
	void pushModalSurface();

	UIWindow* addSurface(const String& name);

	/// Destroys a surface from its children
	void destroySurface(UIWindow* surface);

	void applyPendingChanges();

	typedef std::vector<UIView*> ControlList;

	/// Makes a list of controls from a selector - CSS like
	ControlList selectControls(const String& selector);

	void showMessageBox(const String& message);

	UICore& getContext();

	/// Draw the UI
	void draw(GraphicsDevice* renderer);

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
	UIWindow* operator[](const String& name);

	Color m_topBorderColor, m_bottomBorderColor, m_leftBorderColor, m_rightBorderColor;
	Color m_backgroundColor;
private:
	/// The bounds of the window
	/// In nearly every case, the bounds match exactly the dimensions of the screen
	/// But for particular reasons, the working area of the user interface system can be smaller or bigger.
	Rect<float> m_bounds;

	/// Multiple layers in the interface controls
	/// m_surfaces[0] is the top layer, the closer to the user
	std::vector<UIWindow*> m_surfaces;

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
		UIWindow* surface;
	} PendingChange;

	std::vector<PendingChange> m_pendingChanges;

	int m_surfaceContainerLock;
};

NEPHILIM_NS_END
#endif // NephilimUICanvas_h__