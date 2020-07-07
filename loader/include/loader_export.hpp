#ifndef LOADER_EXPORT_INCLUDE_HPP
#define LOADER_EXPORT_INCLUDE_HPP

#ifdef _WIN32
#ifdef loader_EXPORTS
#define LOADER_API extern "C" __declspec(dllexport)
#else
#define LOADER_API extern "C" __declspec(dllimport)
#endif
#else
#define LOADER_API __attribute__((visibility("default")))
#endif
#endif

