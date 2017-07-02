#pragma once

#ifndef MTYPES_EXPORT_H
#define MTYPES_EXPORT_H

#if defined(_MSC_VER)
    //  Microsoft 
#	ifdef mtypes_EXPORTS
		/* We are building this library */
#		define MTYPES_EXPORT __declspec(dllexport)
#	else
		/* We are using this library */
#	    define MTYPES_EXPORT __declspec(dllimport)
#	endif

#elif defined(__GNUC__)
    //  GCC
    #define MTYPES_EXPORT __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define MTYPES_EXPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#endif
