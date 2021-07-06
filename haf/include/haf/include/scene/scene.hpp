#ifndef HAF_SCENE_SCENE_INCLUDE_HPP
#define HAF_SCENE_SCENE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::scene
{
class SceneManager;

class HAF_API Scene : public SceneNode
{
public:
    explicit Scene(htps::str name);
    virtual htps::str nextSceneName();
    virtual void onFinished();

private:
    htps::rptr<SceneManager> scene_manager_;
    friend class SceneController;
};
}  // namespace haf::scene

#endif
