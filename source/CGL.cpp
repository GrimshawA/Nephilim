#include <Nephilim/CGL.h>


void cglPrepareExtensions()
{
#if defined NEPHILIM_DESKTOP
	glewInit();
#endif
}
