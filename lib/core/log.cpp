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
            function<void(const char*const log_str)> userLogFunction{
                [](const char*const log_str) 
                {
                    std::cout << log_str;
                    std::cout.flush();
#ifdef _MSC_VER
                    OutputDebugString(log_str);
#endif
                }
            };
        }

        void init_log(function<void(const char*const)> f)
        {
            std::swap(userLogFunction, f);
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
