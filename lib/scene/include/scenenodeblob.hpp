#pragma once

#ifndef LIB_SCENE_SCENENODE_BLOB_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_BLOB_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::scene
{
class SceneNode;
class SceneManager;

class SceneNodeBlob
{
public:
    SceneNodeBlob(SceneNode &provider, rptr<SceneManager> scene_manager);

    const SceneManager &sceneManager() const noexcept;
    SceneManager &sceneManager() noexcept;

private:
    SceneNode &scene_node_;
    rptr<SceneManager> scene_manager_{nullptr};
    friend class SceneController;
};
} // namespace lib::scene

#endif
