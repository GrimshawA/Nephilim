#include <Nephilim/Surface.h>

#include <stdio.h>

NEPHILIM_NS_BEGIN

void Surface::create()
{
    printf("Surface::create\n");
	window = new Window();
	window->create(1024,768);
};


NEPHILIM_NS_END
