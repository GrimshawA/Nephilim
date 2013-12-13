#include <Nephilim/UIImage.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/Logger.h>


NEPHILIM_NS_BEGIN

UIImage::UIImage()
{
	t.loadFromFile("logo.png");
};

/// Reload all graphics because they were destroyed and are unavailable now
void UIImage::reloadGraphicalAssets()
{
	t.loadFromFile(m_path);
//	TESTLOG("LOADED UIIMAGE AGAIN!")


}

/// Set the image of the control
void UIImage::setImage(const String& path)
{
	m_path = path;
	t.loadFromFile(path);
}

void UIImage::draw(Renderer* renderer)
{
	Sprite s;
	s.setPosition(mRect.left, mRect.top);
	s.setTexture(t);
	s.resize(mRect.width, mRect.height);
	renderer->draw(s);
};


NEPHILIM_NS_END
