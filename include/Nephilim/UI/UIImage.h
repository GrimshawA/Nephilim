#ifndef UIImage_h__
#define UIImage_h__

#include "Platform.h"
#include "UIView.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIImage : public UIView
{
public:
	UIImage();

	/// Set the image of the control
	void setImage(const String& path);

	/// Reload all graphics because they were destroyed and are unavailable now
	virtual void reloadGraphicalAssets();

	void draw(Renderer* renderer);

	Texture t;

	String m_path;
};

NEPHILIM_NS_END
#endif // UIImage_h__
