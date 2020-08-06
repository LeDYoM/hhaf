#ifndef HAF_EXPORT_INCLUDE_HPP
#define HAF_EXPORT_INCLUDE_HPP

#ifdef _WIN32
#ifdef haf_EXPORTS
//#define HAF_API __declspec(dllexport)
#define HAF_API
#else
//#define HAF_API __declspec(dllimport)
#define HAF_API
#endif
#else
#define HAF_API __attribute__((visibility("default")))
#endif
#endif
