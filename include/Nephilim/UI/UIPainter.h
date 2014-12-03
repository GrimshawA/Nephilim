#ifndef NephilimUI_UIPainter_h__
#define NephilimUI_UIPainter_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Rect.h>
#include <Nephilim/Color.h>

NEPHILIM_NS_BEGIN
class GraphicsDevice;
class Font;
class String;

namespace PainterFlags
{
	enum DrawFlags
	{
		AlignCenterV = 1 << 0,
		AlignCenterH = 1 << 1
	};
}

/**
	\class UIPainter
	\brief This object is passed around to draw functions around the UI to paint itself

	Note:
	The painter is being developed as a part of the UI module. It may not be exclusive to UI in the future though,
	and used for other low level rendering tasks like preparing vector graphics in CPU. That won't make code invalid
	as if the class changes it will still have a typedef for UIPainter for all code to remain valid.

	Note 2: 
	A nice optimization is to batch orders and commit everything at once in the end, either RAII on the destructor or with a commit() function.

	This is a state based painter utility, for quickly putting high quality graphics together for UI.
	The class can also render with GPU with full acceleration.
*/
class NEPHILIM_API UIPainter
{
public:

	mat4 baseMatrix;
	GraphicsDevice* graphicsDevice = nullptr;

	/// Current color used for drawing rects etc
	Color currentColor = Color(50,50,50);

	/// Currently active font, all text is rendered by default with it
	Font* activeFont = nullptr;

public:

	/// Draw a rectangle
	void drawRect(FloatRect rectangle);

	/// Renders the text at the current origin
	void drawText(const String& text);

	/// Renders the text at the current origin
	void drawText(Vector2D point, const String& text);

	/// Renders the text at the current origin
	void drawText(FloatRect rectangle, int flags, const String& text);
};

NEPHILIM_NS_END
#endif //NephilimUI_UIPainter_h__

