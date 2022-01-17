#ifndef LOADER_EXPORT_INCLUDE_HPP
#define LOADER_EXPORT_INCLUDE_HPP

#ifdef _WIN32
#ifdef loader_EXPORTS
#define LOADER_API __declspec(dllexport)
#define LOADER_PRIVATE
#else
#define LOADER_API __declspec(dllimport)
#define LOADER_PRIVATE
#endif
#else
#define LOADER_API __attribute__((visibility("default")))
#define LOADER_PRIVATE __attribute__((visibility("hidden")))
#endif
#endif
