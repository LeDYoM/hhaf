#ifndef LOGGER_LOGINIT_INCLUDE_HPP
#define LOGGER_LOGINIT_INCLUDE_HPP

namespace logger
{

/**
 * @brief Log RAII object to construct and destruct the log
 * automatically.
 *
 * @tparam LogType The logger type to manage.
 */
template <typename LogType>
struct LogInitializer final
{
    /**
     * @brief Construct a new Log Initializer object. It will initialize the
     * static log type.
     */
    constexpr LogInitializer() noexcept { LogType::init_log(); }

    /**
     * @brief Destroy the Log Initializer object. It will finish the static
     * log type.
     */
    constexpr ~LogInitializer() noexcept { LogType::finish_log(); }
};

}  // namespace logger

#endif
