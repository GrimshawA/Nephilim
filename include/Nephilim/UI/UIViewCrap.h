#ifndef PARABOLA_UIVIEW_H
#define PARABOLA_UIVIEW_H

#include <Nephilim/Platform.h>
#include "Rect.h"
#include <vector>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIView{
public:

private:
	std::vector<UIView*> m_children;
	Rect<float> mRect;
};

NEPHILIM_NS_END
#endif