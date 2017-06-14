
#ifndef MTYPES_EXPORT_H
#define MTYPES_EXPORT_H

#ifdef MTYPES_STATIC_DEFINE
#  define MTYPES_EXPORT
#  define MTYPES_NO_EXPORT
#else
#  ifndef MTYPES_EXPORT
#    ifdef mtypes_EXPORTS
        /* We are building this library */
#      define MTYPES_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define MTYPES_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef MTYPES_NO_EXPORT
#    define MTYPES_NO_EXPORT 
#  endif
#endif

#ifndef MTYPES_DEPRECATED
#  define MTYPES_DEPRECATED __declspec(deprecated)
#endif

#ifndef MTYPES_DEPRECATED_EXPORT
#  define MTYPES_DEPRECATED_EXPORT MTYPES_EXPORT MTYPES_DEPRECATED
#endif

#ifndef MTYPES_DEPRECATED_NO_EXPORT
#  define MTYPES_DEPRECATED_NO_EXPORT MTYPES_NO_EXPORT MTYPES_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MTYPES_NO_DEPRECATED
#    define MTYPES_NO_DEPRECATED
#  endif
#endif

#endif
