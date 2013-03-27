#ifndef PARABOLA_UIVIEW_H
#define PARABOLA_UIVIEW_H

#include "Platform.h"
#include "Rect.h"
#include <vector>

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API UIView{
public:

private:
	std::vector<UIView*> m_children;
	Rect<float> m_bounds;
};

PARABOLA_NAMESPACE_END
#endif