#ifndef HTYPES_EXPORT_INCLUDE_HPP
#define HTYPES_EXPORT_INCLUDE_HPP

#ifdef _WIN32
#ifdef htypes_EXPORTS
#define HTYPES_API __declspec(dllexport)
#else
#define HTYPES_API __declspec(dllimport)
#endif
#else
#define HTYPES_API __attribute__((visibility("default")))
#endif
#endif

