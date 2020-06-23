#pragma once

#ifndef HAF_SCENE_INTERFACE_GETTER_INCLUDE_HPP
#define HAF_SCENE_INTERFACE_GETTER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/interfaceaccess.hpp>
#include <haf/system/include/systemaccess.hpp>

namespace haf::scene
{

class InterfaceGetter
{
public:
    explicit InterfaceGetter(
        mtps::rptr<sys::SystemAccess> system_access) noexcept :
        system_access_{system_access}
    {}

    template <typename T>
    T& systemInterface()
    {
        return sys::getInterface<T>(*system_access_);
    }

    template <typename T>
    T const& systemInterface() const
    {
        return sys::getInterface<T>(*system_access_);
    }

private:
    mtps::rptr<sys::SystemAccess> const system_access_;
};

}  // namespace haf::scene

#endif
