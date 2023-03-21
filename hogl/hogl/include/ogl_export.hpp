#ifndef HAF_OGL_EXPORT_INCLUDE_HPP
#define HAF_OGL_EXPORT_INCLUDE_HPP

#ifdef _WIN32
#ifdef hogl_EXPORTS
#define HOGL_API __declspec(dllexport)
#else
#define HOGL_API __declspec(dllimport)
#endif
#else
#define HOGL_API __attribute__((visibility("default")))
#endif
#endif
