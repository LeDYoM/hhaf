#ifndef HAF_SCENE_SCENE_INCLUDE_HPP
#define HAF_SCENE_SCENE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <haf/include/haf_export.hpp>
#include <haf/include/scene/scene_node.hpp>

namespace haf::scene
{
class SceneManager;
class CameraComponent;

class HAF_API Scene : public SceneNode
{
public:
    explicit Scene(htps::str name);
    ~Scene() override;
    void onCreated() override;
    virtual htps::str nextSceneName();
    virtual void onFinished();

    void installDebugUtils();

    htps::sptr<CameraComponent> const& cameraComponent();
    htps::sptr<CameraComponent> const& cameraComponent() const;
    htps::rptr<Scene> sceneParent() override;
    htps::rptr<Scene const> sceneParent() const override;

private:
    class ScenePrivate;
    htps::PImplPointer<ScenePrivate> p_;
    htps::rptr<ScenePrivate> scenePrivate();
    friend class SceneController;
};
}  // namespace haf::scene

#endif
