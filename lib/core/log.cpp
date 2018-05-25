#include <lib/include/core/log.hpp>
#include <iostream>

#ifdef _MSC_VER
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

namespace lib
{
    namespace log
    {
        namespace
        {
            void userLogFunction(const char*const log_str)
            {
                std::cout << log_str;
                std::cout.flush();
#ifdef _MSC_VER
                OutputDebugString(log_str);
#endif
            }

            log_function log_function_callback{ userLogFunction };
        }

        void init_log(log_function f)
        {
            if (f) {
                std::swap(log_function_callback, f);
            }
        }

        void finish_log()
        {
        }

        namespace detail
        {
            void commitlog(str& log_stream) {
                log_stream << "\n";
                userLogFunction(log_stream.c_str());
            }
        }
    }
}
