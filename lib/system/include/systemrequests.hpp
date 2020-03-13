#pragma once

#ifndef LIB_SYSTEM_SYSTEM_REQUESTS_INCLUDE_HPP
#define LIB_SYSTEM_SYSTEM_REQUESTS_INCLUDE_HPP

#include <lib/scene/include/idatawrapper.hpp>

namespace lib::sys
{
/**
 * @brief DataWrapper to perform requests to the system.
 * This class is intended to be instantiated in order to ask the system
 * some questions about states or to set them.
 */
class SystemRequests : public sys::IDataWrapper
{
public:
    /**
     * @brief Tell the system to stop the current aplication.
     */
    void requestExit();

    /**
     * @brief Ask the system about the status of the request to finish the
     *  current aplication.
     * 
     * @return true The system will terminate at the next opportunity.
     * @return false The system has no intention of terminating the current
     *  application.
     */
    bool exitRequested() const;
};
} // namespace lib::sys

#endif
