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

		template<severity_type severity>
		class Logger
		{
		public:
			template<typename...Args >
			constexpr void log(Args...args)
			{
				switch (severity)
				{
				default:
				case severity_type::info:
					log_stream << "<INFO> :";
					break;
				case severity_type::error:
					log_stream << "<ERROR> :";
					break;
				};
				print_impl(args...);
			}

		private:
			str log_stream;

			template<typename T, typename ...Args>
			constexpr void print_impl(T&& value, Args&&... args)
			{
				log_stream << lib::make_str(value, std::forward<Args>(args)...);
				commitlog();
			}

			constexpr void commitlog() {
				log_stream << '\n';
				std::cout << log_stream;
				log_stream = "";
			}
		};
	}
}

#endif
