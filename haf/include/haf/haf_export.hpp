#pragma once

#ifndef HAF_EXPORT_INCLUDE_HPP
#define HAF_EXPORT_INCLUDE_HPP

#ifdef _WIN32
#ifdef haf_EXPORTS
#define HAF_API
//#define HAF_API __declspec(dllexport)
#define HAF__API __declspec(dllexport)
#else
#define HAF_API
//#define HAF_API __declspec(dllexport)
#define HAF__API __declspec(dllimport)
#endif
#else
#define HAF_API __attribute__((visibility("default")))
#define HAF__API __attribute__((visibility("default")))
#endif
#endif
