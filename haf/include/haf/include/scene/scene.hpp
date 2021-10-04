#ifndef HAF_SCENE_SCENE_INCLUDE_HPP
#define HAF_SCENE_SCENE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/scene/scenenode.hpp>

namespace haf::scene
{
class SceneManager;

class HAF_API Scene : public SceneNode
{
public:
    explicit Scene(htps::str name);

    void onCreated();
    virtual htps::str nextSceneName();
    virtual void onFinished();

private:
    types::rptr<SceneManager> scene_manager_;
    friend class SceneController;
};
}  // namespace haf::scene

#endif
