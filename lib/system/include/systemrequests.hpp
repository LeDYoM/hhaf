#pragma once

#ifndef LIB_SYSTEM_SYSTEM_REQUESTS_INCLUDE_HPP
#define LIB_SYSTEM_SYSTEM_REQUESTS_INCLUDE_HPP

#include <lib/scene/include/idatawrapper.hpp>

namespace lib::sys
{

class SystemRequests : public scene::IDataWrapper
{
public:
    void requestExit();
    bool exitRequested() const;
};
} // namespace lib::sys

#endif
