#include <Nephilim/Graphics/CGL.h>


void cglPrepareExtensions()
{
#if defined NEPHILIM_DESKTOP
	glewInit();
#endif
}
