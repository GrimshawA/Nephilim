#include <Nephilim/Surface.h>

#include <stdio.h>

PARABOLA_NAMESPACE_BEGIN

void Surface::create()
{
    printf("Surface::create\n");
	window = new Window();
	window->create(1024,768);
};


PARABOLA_NAMESPACE_END
