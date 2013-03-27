#ifndef UIContextMenu_h__
#define UIContextMenu_h__

#include "Platform.h"
#include "UIControl.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup UserInterface
	\class UIContextMenu
	\brief A special control that is usually spawned by a right mouse click
*/
class PARABOLA_API UIContextMenu : public UIControl{
public:
	void draw(Renderer* renderer);
};

PARABOLA_NAMESPACE_END
#endif // UIContextMenu_h__
