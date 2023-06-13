HAF_PRAGMA_ONCE
#ifndef HAF_PRIVATE_API_INCLUDE_HPP
#define HAF_PRIVATE_API_INCLUDE_HPP

#ifdef _WIN32
#define HAF_PRIVATE
#else
#define HAF_PRIVATE __attribute__((visibility("hidden")))
#endif
#endif
