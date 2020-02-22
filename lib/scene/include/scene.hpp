#pragma once

#ifndef LIB_SCENE_SCENE_INCLUDE_HPP
#define LIB_SCENE_SCENE_INCLUDE_HPP

#include "scenenode.hpp"

#include <mtypes/include/types.hpp>

namespace lib::scene
{
class Scene : public SceneNode
{
public:
    explicit Scene(str name) : SceneNode{nullptr, std::move(name)} {}
    virtual void onFinished() {}
};
} // namespace lib::scene

#endif
