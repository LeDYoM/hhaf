#pragma once

#ifndef LIB_SCENE_SCENEMETRICS_INCLUDE_HPP
#define LIB_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/include/idatawrapper.hpp>

namespace lib::scene
{
class SceneMetrics : public IDataWrapper
{
public:
    Rectf32 currentView() noexcept;
};
} // namespace lib::scene

#endif
