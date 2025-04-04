HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_SCENE_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <haf/include/haf_export.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/properties/basic_property.hpp>

namespace haf::scene
{
class SceneManager;
class CameraComponent;

class HAF_API SceneComponent : public component::Component
{
public:
    SceneComponent();
    ~SceneComponent() override;
    void onAttached() override;
    virtual htps::str nextSceneName();
    virtual void onFinished();

    void installDebugUtils();

    //    prop::BasicProperty<htps::str> name;
    htps::sptr<CameraComponent> const& cameraComponent();
    htps::sptr<CameraComponent> const& cameraComponent() const;
    /*
        htps::rptr<SceneComponent> sceneParent() override;
        htps::rptr<SceneComponent const> sceneParent() const override;
    */
    htps::str completeName() const;

    void initDebugUtils();

private:
    class SceneComponentPrivate;
    htps::PImplPointer<SceneComponentPrivate> p_;
    htps::rptr<SceneComponentPrivate> scenePrivate();
    friend class SceneController;
};
}  // namespace haf::scene

#endif
