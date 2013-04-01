#ifndef PARABOLAPLATFORM_H
#define PARABOLAPLATFORM_H

/// NEPHILIM_SFML - Does this platform use SFML for windowing?

/**
	\namespace pE
	\brief Contains every part of Nephilim
*/
#define NEPHILIM_NS_BEGIN namespace pE{
#define NEPHILIM_NS_END }

// -- Windows
#ifdef _WIN32
        #ifdef _MSC_VER
            #pragma warning(disable : 4251) // annoying dll warning
            #pragma warning(disable : 4275) // annoying dll warning
			#pragma warning(disable : 4355) // warning this in base member initialiser list

            #define PARABOLA_COMPILER "msvc"
            #define PARABOLA_COMPILER_MSVC
            #define _CRT_SECURE_NO_DEPRECATE

        #else //GCC
            #define PARABOLA_COMPILER "gcc"
            #define PARABOLA_COMPILER_GCC
        #endif
		#define NEPHILIM_SFML
		#define SFML_STATIC
		#define PARABOLA_WINDOWS
		#define PARABOLA_OS "win"
		#define PARABOLA_DESKTOP
		#define NEPHILIM_DESKTOP

		#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
		#endif

// -- Linux: Desktop
#elif (defined __linux__ || defined LINUX) && !defined ANDROID
		#define NEPHILIM_LINUX
		#define NEPHILIM_UNIX
		#define NEPHILIM_DESKTOP
		#define NEPHILIM_SFML


// -- Apple: OS X or iPad/iPod/iPhone
#elif defined __APPLE_CC__ || defined __APPLE__
	#define NEPHILIM_UNIX
    #define NEPHILIM_APPLE
    #include "TargetConditionals.h"

	#ifdef TARGET_OS_IPHONE
		#define NEPHILIM_IOS
	#else
		#define NEPHILIM_OSX
	#endif

// -- Android platform
#elif defined ANDROID_NDK || defined ANDROID
	#define PARABOLA_ANDROID
	#define PARABOLA_GLES
	#define PARABOLA_NOSFML
    #define PARABOLA_UNIX
	#define NEPHILIM_COMPILER "gcc"
	#define NEPHILIM_UNIX
	#define NEPHILIM_ANDROID

#endif


// -- 32/64 bit platform
#if defined __x86_64__ || defined _M_X64 || defined __powerpc64__ || defined __alpha__ || defined __ia64__ || defined __s390__ || defined __s390x__
   #define NEPHILIM_ARCH_64
#else
   #define NEPHILIM_ARCH_32
#endif


// -- DLL/SO Exports to compile as dynamic library
#if defined NEPHILIM_DYNAMIC
	#define NEPHILIM_API __declspec(dllexport)
#else
	#define NEPHILIM_API
#endif

// -- Release mode
#if defined _DEBUG || defined DEBUG
	#define NEPHILIM_DEBUG
#else
	#define NEPHILIM_RELEASE
#endif

// -- Fixed size types
NEPHILIM_NS_BEGIN
typedef signed   char Int8;
typedef unsigned char Uint8;
typedef signed   short Int16;
typedef unsigned short Uint16;
typedef signed   int Int32;
typedef unsigned int Uint32;

#if defined(_MSC_VER)
	typedef signed   __int64 Int64;
	typedef unsigned __int64 Uint64;
#else
	typedef signed   long long Int64;
	typedef unsigned long long Uint64;
#endif
NEPHILIM_NS_END

#ifndef NULL
#define NULL 0
#endif

#endif
