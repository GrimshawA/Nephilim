#ifndef Platform_h__
#define Platform_h__


/// NEPHILIM_NOASSIMP   - Do not compile AssimpConverter at all
/// NEPHILIM_SFML       - Defined for platforms that use SFML to manage a window
/// NEPHILIM_NOPROFILER - Disables the profiling tools globally if defined
/// NEPHILIM_GLES1		- Define this globally so the engine uses a OpenGL ES 1.1 renderer by default

/**
	\namespace pE
	\brief Contains every part of Nephilim
*/
#define NEPHILIM_NS nx
#define NEPHILIM_NS_BEGIN namespace nx{
#define NEPHILIM_NS_END }

// -- Windows
#ifdef _WIN32
        #ifdef _MSC_VER
            #pragma warning(disable : 4251) // annoying dll warning
            #pragma warning(disable : 4275) // annoying dll warning
			#pragma warning(disable : 4355) // warning this in base member initialiser list

            #define NEPHILIM_COMPILER "vs"
            #define NEPHILIM_COMPILER_VS
            #define _CRT_SECURE_NO_DEPRECATE

        #else //GCC
            #define NEPHILIM_COMPILER "gcc"
            #define NEPHILIM_COMPILER_GCC
        #endif

		#define NEPHILIM_SFML
		#define SFML_STATIC
		#define NEPHILIM_OS "windows"
		#define NEPHILIM_WINDOWS
		#define NEPHILIM_DESKTOP

// -- Linux: Desktop
#elif (defined __linux__ || defined LINUX) && !defined ANDROID
		#define NEPHILIM_LINUX
		#define NEPHILIM_UNIX
		#define NEPHILIM_DESKTOP
		#define NEPHILIM_SFML
		#define NEPHILIM_OS "linux"

// -- Apple: OS X or iPad/iPod/iPhone
#elif defined __APPLE_CC__ || defined __APPLE__
	#define NEPHILIM_UNIX
    #define NEPHILIM_APPLE
    #include "TargetConditionals.h"

	#if TARGET_OS_IPHONE == 1
		#define NEPHILIM_IOS
		#define NEPHILIM_OS "ios"
		#define NEPHILIM_GLES
	#else
		#define NEPHILIM_OSX
		#define NEPHILIM_DESKTOP
		#define NEPHILIM_OS "osx"
	#endif

// -- Android platform
#elif defined ANDROID_NDK || defined ANDROID
	#define NEPHILIM_COMPILER "gcc"
	#define NEPHILIM_UNIX
	#define NEPHILIM_ANDROID
	#define NEPHILIM_OS "android"
	#define NEPHILIM_GLES
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

#endif // Platform_h__
