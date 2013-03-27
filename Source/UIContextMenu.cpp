#include <Nephilim/UIContextMenu.h>
#include <Nephilim/Text.h>

PARABOLA_NAMESPACE_BEGIN

void UIContextMenu::draw(Renderer* renderer){
	renderer->drawDebugQuad(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2, 0,m_bounds.width, m_bounds.height, Color(10,20,10) );
	Text te;
	te.setCharacterSize(10);
	te.setString("Nothing");
	te.setPosition(m_bounds.left, m_bounds.top);
	renderer->draw(te);
};

PARABOLA_NAMESPACE_END