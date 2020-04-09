#pragma once

#ifndef HAF_MAIN_INCLUDE_HPP
#define HAF_MAIN_INCLUDE_HPP

 // Identify the operating system
// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
#ifdef _WIN32
	#define HAF_SYSTEM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	// Apple platform, see which one it is
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		// iOS
		#define HAF_SYSTEM_IOS
	#elif TARGET_OS_MAC
		// MacOS
		#define HAF_SYSTEM_MACOS
	#else
		// Unsupported Apple system
		#error This Apple operating system is not supported
		#define HAF_SYSTEM_MAC_UNSUPPORTED
	#endif
#elif defined(__unix__)
	// UNIX system, see which one it is
	#if defined(__ANDROID__)
		// Android
		#define HAF_SYSTEM_ANDROID
	#elif defined(__linux__)
		// Linux
		#define HAF_SYSTEM_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		// FreeBSD
		#define HAF_SYSTEM_FREEBSD
	#else
		// Unsupported UNIX system
		#define HAF_SYSTEM_UNIX_UNSUPPORTED
		#error This UNIX operating system is not supported by lib library
	#endif
#else
		// Unsupported system
		#define HAF_SYSTEM_UNSUPPORTED
		#error This operating system is not supported by lib library
#endif

#ifdef HAF_SYSTEM_WINDOWS
	#ifdef DYNAMIC_LINKING
		#ifdef HAF_EXPORTS
			#define HAF_API_EXPORT __declspec(dllexport)
		#else
			#define HAF_API_IMPORT __declspec(dllimport)
		#endif
	#else
		#define HAF_API_EXPORT
		#define HAF_API_IMPORT
	#endif
#else // Linux, FreeBSD, Mac OS X
	#if __GNUC__ >= 4
		// GCC 4 has special keywords for showing/hiding symbols,
		// the same keyword is used for both importing and exporting
		#define HAF_API_EXPORT __attribute__ ((__visibility__ ("default")))
		#define HAF_API_IMPORT __attribute__ ((__visibility__ ("default")))
	#else
		// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
		#define HAF_API_EXPORT
		#define HAF_API_IMPORT
	#endif
#endif

#endif
