#include <Nephilim/UIContextMenu.h>
#include <Nephilim/Text.h>

NEPHILIM_NS_BEGIN

void UIContextMenu::draw(Renderer* renderer){
	renderer->drawDebugQuad(mRect.left + mRect.width/2, mRect.top + mRect.height/2, 0,mRect.width, mRect.height, Color(10,20,10) );
	Text te;
	te.setCharacterSize(10);
	te.setString("Nothing");
	te.setPosition(mRect.left, mRect.top);
	renderer->draw(te);
};

NEPHILIM_NS_END