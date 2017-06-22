#pragma once

#ifndef LIB_LOG_INCLUDE_HPP
#define LIB_LOG_INCLUDE_HPP

#include "mtypes_export.h"
#include "str.hpp"

namespace lib
{
	namespace log
	{
		enum severity_type
		{
			info,
			error,
		};

		template<severity_type severity, typename...Args >
		constexpr void log(Args...args)
		{
			str log_stream(detail::severity_txt<severity>());
			log_stream << detail::print_impl(args...);
			detail::commitlog(log_stream);
		}

		namespace detail
		{
			template<severity_type severity>
			constexpr const char*const severity_txt()
			{
				switch (severity)
				{
				default:
				case severity_type::info:
					return "<INFO> :";
					break;
				case severity_type::error:
					return "<ERROR> :";
					break;
				}
			}

			template<typename T, typename ...Args>
			constexpr const str print_impl(T&& value, Args&&... args)
			{
				return lib::make_str(value, std::forward<Args>(args)...);
			}

			inline void commitlog(str& log_stream) {
				log_stream << '\n';
				std::cout << log_stream;
			}
		}
	}
}

#endif
