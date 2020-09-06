#pragma once

#ifndef HAF_BACKEND_CLIENT_EXPORT_INCLUDE_HPP
#define HAF_BACKEND_CLIENT_EXPORT_INCLUDE_HPP

#ifdef _WIN32
#ifdef backend_client_EXPORTS
#define BC_API /* __declspec(dllexport) */
#else
#define BC_API /* __declspec(dllexport) */
#endif
#else
#define BC_API __attribute__((visibility("default")))
#endif
#endif
