#ifndef HAF_SYSTEM_INTERFACE_GETTER_INCLUDE_HPP
#define HAF_SYSTEM_INTERFACE_GETTER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/system/include/interfaceaccess.hpp>

namespace haf::sys
{
    class SystemAccess;
}

namespace haf::sys
{
class InterfaceGetter
{
public:
    explicit InterfaceGetter(
        htps::rptr<SystemAccess> system_access) noexcept :
        system_access_{system_access}
    {}

    template <typename T>
    T& systemInterface()
    {
        return getInterface<T>(*system_access_);
    }

    template <typename T>
    T const& systemInterface() const
    {
        return sys::getInterface<T>(*system_access_);
    }

private:
    htps::rptr<SystemAccess> const system_access_;
};

}  // namespace haf::scene

#endif
