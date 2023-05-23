HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_APP_INITIALIZER_INCLUDE_HPP
#define HAF_SCENE_APP_INITIALIZER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_factory.hpp>

namespace haf::scene
{
/**
 * @brief SubSystem to be used as the first subsystem
 * that an app will receive. It contains the necessary methods to
 * initialize the app and perform some actions in the system
 */
class IAppInitializer
{
protected:
    ~IAppInitializer() = default;

public:
    virtual bool registerComponent(
        core::str_view componentType,
        component::ComponentCreateFunction component_create_function) = 0;

    template <typename T>
    bool registerComponent()
    {
        static_assert(std::is_base_of_v<component::Component, T>,
                      "The template type must be inherited from Scene");
        return registerComponent(T::StaticTypeName,
                                 []() { return core::msptr<T>(); });
    }

    virtual bool instanciateRootComponent(core::str_view componentType) = 0;
};

}  // namespace haf::scene

#endif
