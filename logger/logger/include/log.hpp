#pragma once

#ifndef LIB_MTYPES_LOG_INCLUDE_HPP
#define LIB_MTYPES_LOG_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/function.hpp>
#include <iostream>

namespace lib::log
{
    inline void init_log() {}
    inline void finish_log() {}

    enum severity_type { info, error };
    enum level_type { debug, release };

    constexpr level_type compiled_log_level_type = level_type::debug;

    template <level_type level>
    constexpr bool compile_logs = compiled_log_level_type <= level;

    namespace detail
    {
        template<severity_type severity>
        constexpr const auto severity_txt() noexcept
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

        inline void commitlog(str& log_stream) 
        {
            log_stream << "\n";
            std::cout << log_stream.c_str();
            std::cout.flush();
        }
    }
    
    template<level_type level, severity_type severity, typename...Args>
    constexpr void log(Args&&...args) noexcept
    {
        if constexpr (compile_logs<level>)
        {
            str log_stream(detail::severity_txt<severity>());
            log_stream << make_str(std::forward<Args>(args)...);
            detail::commitlog(log_stream);
        }
    }
}

namespace lib
{
	template<typename ...Args>
	constexpr void log_debug_info(Args&&... args) noexcept 
	{
		log::log<log::level_type::debug, log::severity_type::info>(std::forward<Args>(args)...);
	}

	template<typename ...Args>
	constexpr void log_debug_error(Args&&... args) noexcept 
	{
		log::log<log::level_type::debug, log::severity_type::error>(std::forward<Args>(args)...);
	}

	template<typename ...Args>
	constexpr void log_release_info(Args&&... args) noexcept 
	{
		log::log<log::level_type::release, log::severity_type::info>(std::forward<Args>(args)...);
	}

	template<typename ...Args>
	constexpr void log_release_error(Args&&... args) noexcept {
        log::log<log::level_type::release, log::severity_type::error>(std::forward<Args>(args)...);
	}

	template<typename ...Args>
	constexpr void assert_debug(const bool condition, Args&&... args) noexcept {
		if (!condition) { log_debug_error(std::forward<Args>(args)...); }
	}

	template<typename ...Args>
	constexpr void assert_release(const bool condition, Args&&... args) noexcept {
		if (!condition) { log_release_error(std::forward<Args>(args)...); }
	}
}

#define CLIENT_EXECUTE_IN_DEBUG(x)	x

#endif
