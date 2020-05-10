#pragma once

#ifndef HAF_LOGGER_LOGINIT_INCLUDE_HPP
#define HAF_LOGGER_LOGINIT_INCLUDE_HPP

namespace logger
{

/**
 * @brief Log RAII object to construct and destruct the log
 * automatically..
 *
 * @tparam LogType The logger type to manage.
 */
template <typename LogType>
class LogInitializer
{
public:
    /**
     * @brief Construct a new Log Initializer object. It will initialize the
     * static log type.
     */
    LogInitializer() { LogType::init_log(); }

    /**
     * @brief Destroy the Log Initializer object. It will finish the static
     * log type.
     */
    ~LogInitializer() { LogType::finish_log(); }
};

}  // namespace logger

#endif
