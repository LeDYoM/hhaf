#ifndef HAF_BACKEND_BACKEND_FACTORY_UTILS_INCLUDE_HPP
#define HAF_BACKEND_BACKEND_FACTORY_UTILS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend/include/backend_register.hpp>

namespace haf::backend
{
template <typename FactoryType>
bool fillFactory(htps::uptr<BackendRegister> const& backend_register,
                 FactoryType** factory_to_fill)
{
    if (auto factory{backend_register->getFactory<IFactoryOf<FactoryType>>()};
        factory != nullptr)
    {
        (*factory_to_fill) = factory->create();
        return (*factory_to_fill) != nullptr;
    }
    return false;
}

template <typename FactoryType, typename... FactoryTypes>
bool fillFactories(htps::uptr<BackendRegister> const& backend_register,
                   FactoryType factory_to_fill,
                   FactoryTypes... factories_to_fill)
{
    bool result{fillFactory(backend_register, factory_to_fill)};

    if constexpr (sizeof...(FactoryTypes) > 0U)
    {
        result &= fillFactories(backend_register, factories_to_fill...);
    }

    return result;
}

template <typename FactoryType>
bool emptyFactory(htps::uptr<BackendRegister> const& backend_register,
                  FactoryType** factory_to_empty)
{
    if (auto factory(backend_register->getFactory<IFactoryOf<FactoryType>>());
        factory != nullptr)
    {
        if (factory_to_empty != nullptr && *factory_to_empty != nullptr)
        {
            factory->destroy(*factory_to_empty);
            (*factory_to_empty) = nullptr;
            return true;
        }
    }
    return false;
}

template <typename FactoryType, typename... FactoryTypes>
bool emptyFactories(htps::uptr<BackendRegister> const& backend_register,
                    FactoryType factory_to_empty,
                    FactoryTypes... factories_to_empty)
{
    bool result = emptyFactory(backend_register, factory_to_empty);

    if constexpr (sizeof...(FactoryTypes) > 0U)
    {
        result &= emptyFactories(backend_register, factories_to_empty...);
    }

    return result;
}
}  // namespace haf::backend
#endif
