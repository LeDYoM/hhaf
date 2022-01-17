#ifndef HTYPES_DEBUG_INTERNAL_INCLUDE_HPP
#define HTYPES_DEBUG_INTERNAL_INCLUDE_HPP

#ifdef LOG_MODE
#include <iostream>
#endif

namespace htps
{
#ifdef LOG_MODE
#define LOG(x) std::cout << x << std::endl;
#define LOG_TOKEN(t) \
    LOG("Token: " << int(t.token_type) << "\t: " << t.value.c_str());
#else
#define LOG(x)
#define LOG_TOKEN(t)
#endif
}  // namespace htps

#endif
