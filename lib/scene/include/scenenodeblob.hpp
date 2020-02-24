#pragma once

#ifndef LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

namespace lib
{
class IApp;
} // namespace lib

namespace lib::sys
{
class RandomSystem;
} // namespace lib::sys

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

    const sys::RandomSystem &randomSystem() const noexcept;
    sys::RandomSystem &randomSystem() noexcept;

    const IApp &app() const;
    IApp &app();

    template <typename T>
    T &app() { return (static_cast<T &>(app())); }

private:
    SceneNode &scene_node_;
    rptr<SceneManager> scene_manager_{nullptr};
    friend class SceneController;
};
} // namespace lib::scene

#endif
