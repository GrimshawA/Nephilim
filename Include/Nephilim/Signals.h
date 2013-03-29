#ifndef PARABOLA_SIGNALS_H
#define PARABOLA_SIGNALS_H

#include <sigc++/sigc++.h>
#include "Platform.h"

NEPHILIM_NS_BEGIN	
	using sigc::ptr_fun;
	using sigc::mem_fun;
	using sigc::signal;

/// Document a define?!
#define MAKE_SLOT_LOCAL(classname, funcname) (mem_fun(this, &classname::funcname))
#define MAKE_SLOT_OBJECT(classname, objectname, funcname) (mem_fun(objectname, &classname::funcname))
#define MAKE_SLOT_FUNCTION(funcname) (ptr_fun(&funcname))


NEPHILIM_NS_END

#endif