#ifndef UIImage_h__
#define UIImage_h__

#include "Platform.h"
#include "UIControl.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API UIImage : public UIControl
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

class ASEngine;
bool registerUIImage(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif // UIImage_h__
