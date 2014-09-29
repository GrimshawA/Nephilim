#include <Nephilim/UI/UIImage.h>
#include <Nephilim/RectangleShape.h>
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

void UIImage::draw(GraphicsDevice* renderer)
{
	RectangleShape s;
	s.setRect(getBounds());
	s.setTexture(&t);
	renderer->draw(s);
};


NEPHILIM_NS_END
