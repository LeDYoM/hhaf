#ifndef __LIB_INCLUDE_COMPILECONFIG_HPP__
#define __LIB_INCLUDE_COMPILECONFIG_HPP__

 // Identify the operating system
// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
#ifdef _WIN32
	#define LIB_SYSTEM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	// Apple platform, see which one it is
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		// iOS
		#define LIB_SYSTEM_IOS
	#elif TARGET_OS_MAC
		// MacOS
		#define LIB_SYSTEM_MACOS
	#else
		// Unsupported Apple system
		#error This Apple operating system is not supported
		#define LIB_SYSTEM_MAC_UNSUPPORTED
	#endif
#elif defined(__unix__)
	// UNIX system, see which one it is
	#if defined(__ANDROID__)
		// Android
		#define LIB_SYSTEM_ANDROID
	#elif defined(__linux__)
		// Linux
		#define LIB_SYSTEM_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		// FreeBSD
		#define LIB_SYSTEM_FREEBSD
	#else
		// Unsupported UNIX system
		#define LIB_SYSTEM_UNIX_UNSUPPORTED
		#error This UNIX operating system is not supported by SFML library
	#endif
#else
		// Unsupported system
		#define LIB_SYSTEM_UNSUPPORTED
		#error This operating system is not supported by SFML library
#endif

// Define a portable debug macro
#if !defined(NDEBUG)
	#define LIB_DEBUG
#endif

#ifdef LIB_SYSTEM_WINDOWS
	#define LIB_API_EXPORT __declspec(dllexport)
	#define LIB_API_IMPORT __declspec(dllimport)
#else // Linux, FreeBSD, Mac OS X
	#if __GNUC__ >= 4
		// GCC 4 has special keywords for showing/hidding symbols,
		// the same keyword is used for both importing and exporting
		#define LIB_API_EXPORT __attribute__ ((__visibility__ ("default")))
		#define LIB_API_IMPORT __attribute__ ((__visibility__ ("default")))
	#else
		// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
		#define LIB_API_EXPORT
		#define LIB_API_IMPORT
	#endif
#endif

#endif
