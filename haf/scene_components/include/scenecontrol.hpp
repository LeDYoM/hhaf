#pragma once

#ifndef HAF_SCENE_SCENE_CONTROL_INCLUDE_HPP
#define HAF_SCENE_SCENE_CONTROL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>

namespace haf::scene
{
class SceneControl : public sys::IDataWrapper
{
public:
    void switchToNextScene();
};
} // namespace haf::scene

#endif
