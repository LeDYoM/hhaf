#pragma once

#ifndef LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define LIB_TIME_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/idatawrapper.hpp>
#include <lib/time/include/timepoint.hpp>

namespace lib::time
{
/// Component to provide access to resources.
class TimeView : public scene::IDataWrapper
{
public:
    TimePoint now() const;
};
} // namespace lib::time

#endif
