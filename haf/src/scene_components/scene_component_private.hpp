HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_COMPNENT_PRIVATE_INCLUDE_HPP
#define HAF_SCENE_SCENE_COMPNENT_PRIVATE_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/debug_system/displayvar_console.hpp>

namespace haf::sys
{
class ISystemProvider;
}

namespace haf::scene
{
class SceneManager;

class SceneComponent::SceneComponentPrivate
{
public:
    explicit SceneComponentPrivate(htps::rptr<SceneComponent> _this) noexcept;
    ~SceneComponentPrivate();

    void setSystemProvider(
        htps::rptr<sys::ISystemProvider> isystem_provider) noexcept;

    htps::rptr<sys::ISystemProvider> iSystemProvider() const noexcept;

    htps::sptr<CameraComponent> camera_component_;
    htps::sptr<haf::DisplayVarConsole> m_display_var_console;

private:
    htps::rptr<SceneComponent> scene_;
    htps::rptr<sys::ISystemProvider> isystem_provider_{nullptr};
};
}  // namespace haf::scene

#endif
