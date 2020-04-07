#pragma once

#ifndef HAF_SCENE_SCENEMETRICS_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/system/include/idatawrapper.hpp>

namespace haf::scene
{
class SceneMetrics : public sys::IDataWrapper
{
public:
    mtps::Rectf32 currentView() const;
};
} // namespace haf::scene

#endif
