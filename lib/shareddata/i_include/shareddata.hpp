#pragma once

#ifndef LIB_SYSTEM_SHARED_DATA_INCLUDE_HPP
#define LIB_SYSTEM_SHARED_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/appservice.hpp>
#include <lib/shareddata/include/ishareable.hpp>

namespace lib::shdata
{

/// SharedDataSystem is a system whose only purpose is to store
/// data shared between different objects.
class SharedDataSystem final : public AppService
{
public:
    SharedDataSystem();
    ~SharedDataSystem() override;

    void store(uptr<IShareable> data);
    uptr<IShareable> retrieve();

private:
    uptr<IShareable> data_;
};
} // namespace lib::sys

#endif
