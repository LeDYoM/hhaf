HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_BOOTSTRAP_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_BOOTSTRAP_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/scene/scene_update_time.hpp>

namespace haf::component
{
template <typename T,
          scene::SceneUpdateTime sceneUpdateTime =
              scene::SceneUpdateTime::Controller>
class ComponentBootStrap : public Component
{
public:
    constexpr core::str_view const staticTypeName() const noexcept override
    {
        return T::StaticTypeName;
    }

    static constexpr scene::SceneUpdateTime StaticSceneUpdateTime{sceneUpdateTime};

protected:
    using Component::Component;

    scene::SceneUpdateTime defaultSceneUpdateTime() const override
    {
        return sceneUpdateTime;
    }

public:
    ~ComponentBootStrap() override{};
};

}  // namespace haf::component

#endif
