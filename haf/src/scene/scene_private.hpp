#ifndef HAF_SCENE_SCENE_PRIVATE_INCLUDE_HPP
#define HAF_SCENE_SCENE_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/scene.hpp>

namespace haf::sys
{
class ISystemProvider;
}
namespace haf::scene
{
class SceneManager;
class Scene;

class Scene::ScenePrivate final
{
public:
    explicit ScenePrivate(htps::rptr<Scene> _this) noexcept;
    void setSystemProvider(
        htps::rptr<sys::ISystemProvider> isystem_provider) noexcept;

    htps::rptr<sys::ISystemProvider> iSystemProvider() const noexcept
    {
        return isystem_provider_;
    }

private:
    htps::rptr<Scene> scene_;
    htps::rptr<sys::ISystemProvider> isystem_provider_{nullptr};
};
}  // namespace haf::scene

#endif
