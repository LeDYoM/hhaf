#include <mtypes/include/log.hpp>
#include <mtypes/include/str.hpp>
#include <iostream>

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
				log_stream << '\n';
				std::cout << log_stream;
			}
		}
	}
}
