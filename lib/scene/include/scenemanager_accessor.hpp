#pragma once

#ifndef LIB_SCENE_SCENENODE_BLOB_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_BLOB_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::sys
{
    class ISystemProvider;
}

namespace lib::scene
{
class SceneManager;

class SceneManagerAccessor
{
public:
    SceneManagerAccessor(rptr<SceneManager> scene_manager);

    const SceneManager &sceneManager() const noexcept;
    SceneManager &sceneManager() noexcept;

    const sys::ISystemProvider& isystemProvider() const noexcept;
    sys::ISystemProvider& isystemProvider() noexcept;

private:
    rptr<SceneManager> scene_manager_{nullptr};
    friend class SceneController;
};
} // namespace lib::scene

#endif
