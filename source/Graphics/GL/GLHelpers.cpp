#include <Nephilim/Graphics/GL/GLHelpers.h>


void cglPrepareExtensions()
{
#if defined NEPHILIM_DESKTOP
	glewInit();
#endif
}
