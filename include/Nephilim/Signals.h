#ifndef PARABOLA_SIGNALS_H
#define PARABOLA_SIGNALS_H

#include <sigc++/sigc++.h>
#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN	

/// Document a define?!
#define MAKE_SLOT_LOCAL(classname, funcname) (sigc::mem_fun(this, &classname::funcname))
#define MAKE_SLOT_OBJECT(classname, objectname, funcname) (sigc::mem_fun(objectname, &classname::funcname))
#define MAKE_SLOT_FUNCTION(funcname) (sigc::ptr_fun(&funcname))

#define SLOT_MFN_LOCAL(classname, funcname) (sigc::mem_fun(this, &classname::funcname))
#define SLOT_MFN(classname, objectname, funcname) (sigc::mem_fun(objectname, &classname::funcname))
#define SLOT_FN(funcname) (sigc::ptr_fun(&funcname))

NEPHILIM_NS_END

#endif