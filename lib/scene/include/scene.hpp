#pragma once

#ifndef LIB_SCENE_SCENE_INCLUDE_HPP
#define LIB_SCENE_SCENE_INCLUDE_HPP

#include "scenenode.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace haf::scene
{
class SceneManager;
class Scene : public SceneNode
{
public:
    explicit Scene(mtps::str name) : SceneNode{nullptr, std::move(name)} {}
    virtual void onFinished() {}
private:
    mtps::rptr<SceneManager> scene_manager_;
    friend class SceneController;
};
} // namespace haf::scene

#endif
