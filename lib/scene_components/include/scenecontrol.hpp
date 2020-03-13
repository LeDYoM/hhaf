#pragma once

#ifndef LIB_SCENE_SCENE_CONTROL_INCLUDE_HPP
#define LIB_SCENE_SCENE_CONTROL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/idatawrapper.hpp>

namespace lib::scene
{
class SceneControl : public sys::IDataWrapper
{
public:
    void switchToNextScene();
};
} // namespace lib::scene

#endif
