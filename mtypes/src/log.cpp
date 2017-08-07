#include <mtypes/include/log.hpp>
#include <mtypes/include/str.hpp>
#include <iostream>

#ifdef _MSC_VER
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

namespace lib
{
	namespace log
	{
		void init_log()
		{
		}
		void finish_log()
		{
		}

		namespace detail
		{
			void commitlog(str& log_stream) {
				log_stream << "\n";
				std::cout << log_stream.c_str();
#ifdef _MSC_VER
				OutputDebugString(log_stream.c_str());
#endif
			}
		}
	}
}
