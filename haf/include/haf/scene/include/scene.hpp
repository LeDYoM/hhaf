#ifndef HAF_SCENE_SCENE_INCLUDE_HPP
#define HAF_SCENE_SCENE_INCLUDE_HPP

#include <haf/haf_export.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::scene
{
class SceneManager;

class HAF_API Scene : public SceneNode
{
public:
    explicit Scene(mtps::str name) : SceneNode{nullptr, std::move(name)} {}
    virtual mtps::str nextSceneName() { return ""; }
    virtual void onFinished() {}

private:
    mtps::rptr<SceneManager> scene_manager_;
    friend class SceneController;
};
}  // namespace haf::scene

#endif
