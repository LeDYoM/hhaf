#include "scenenodeblob.hpp"

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>

namespace lib::scene
{
SceneNodeBlob::SceneNodeBlob(rptr<SceneManager> scene_manager)
    : scene_manager_{std::move(scene_manager)} {}

const SceneManager &SceneNodeBlob::sceneManager() const noexcept
{
    return *scene_manager_;
}

SceneManager &SceneNodeBlob::sceneManager() noexcept
{
    return *scene_manager_;
}

} // namespace lib::scene
