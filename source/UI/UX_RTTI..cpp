#include <Nephilim/UI/UX_RTTI.h>
#include <Nephilim/UI/Widget.h>
#include <Nephilim/UI/UICanvas.h>
#include <Nephilim/UI/UIButton.h>

#include <Nephilim/Foundation/Factory.h>

NEPHILIM_NS_BEGIN

void RegisterUX_RTTI()
{
	REGISTER_FACTORY_CLASS("Widget", Widget);
	REGISTER_FACTORY_CLASS("UICanvas", UICanvas);
	REGISTER_FACTORY_CLASS("UIButton", UIButton);
}

NEPHILIM_NS_END