#ifndef NephilimUI_Image_h__
#define NephilimUI_Image_h__

#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

/**
	\class UIImage
	\brief Control that displays an image
*/
class NEPHILIM_API UIImage : public Widget
{
public:
	UIImage();

	/// Set the image of the control
	void setImage(const String& path);

	/// Reload all graphics because they were destroyed and are unavailable now
	virtual void reloadGraphicalAssets();

	void draw(GraphicsDevice* renderer);

	Texture2D t;

	String m_path;
};

NEPHILIM_NS_END
#endif // NephilimUI_Image_h__
