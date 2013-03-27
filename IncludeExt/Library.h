#ifndef PARABOLA_LIBRARYHELPER_H
#define PARABOLA_LIBRARYHELPER_H

#include "ParabolaCore/Platform.h"

#ifdef PARABOLA_WINDOWS

#ifdef PARABOLA_COMPILER_MSVC
#ifdef AUTOMATIC_LINK_STATIC

#ifdef PARABOLA_BUILD_DEBUG
#pragma comment(lib, "sfml-graphics-s-d.lib")
#pragma comment(lib, "sfml-audio-s-d.lib")
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "sfml-network-s-d.lib")

#pragma comment(lib, "SPARK_debug.lib")
#pragma comment(lib, "SPARK_GL_debug.lib")
#pragma comment(lib, "pugixml_d.lib")

#pragma comment(lib, "box2d-d.lib")
#pragma comment(lib, "enet_d.lib")

#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "libsigc++_d.lib")

#pragma comment(lib, "RocketCore_d.lib")
#pragma comment(lib, "RocketDebugger_d.lib")
#pragma comment(lib, "RocketControls_d.lib")

#pragma comment(lib, "angelscriptd.lib")

#endif

#ifdef PARABOLA_BUILD_RELEASE
#pragma comment(lib, "sfml-graphics-s.lib")
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "sfml-audio-s.lib")
#pragma comment(lib, "sfml-network-s.lib")
#pragma comment(lib, "sfml-window-s.lib")

#pragma comment(lib, "pugixml.lib")
#pragma comment(lib, "SPARK.lib")
#pragma comment(lib, "SPARK_GL.lib")

#pragma comment(lib, "libsigc++.lib")

#pragma comment(lib, "box2d.lib")
#pragma comment(lib, "enet.lib")

#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "RocketCore.lib")
#pragma comment(lib, "RocketDebugger.lib")
#pragma comment(lib, "RocketControls.lib")

#pragma comment(lib, "angelscript.lib")

#endif

#endif
#endif

#endif

#endif