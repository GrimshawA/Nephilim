#ifndef UIContextMenu_h__
#define UIContextMenu_h__

#include "Platform.h"
#include "UIView.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup UserInterface
	\class UIContextMenu
	\brief A special control that is usually spawned by a right mouse click
*/
class NEPHILIM_API UIContextMenu : public UIView{
public:
	void draw(Renderer* renderer);
};

NEPHILIM_NS_END
#endif // UIContextMenu_h__
