#pragma once

#ifndef LIB_SCENE_SCENEMETRICS_INCLUDE_HPP
#define LIB_SCENE_SCENEMETRICS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/system/include/idatawrapper.hpp>

namespace lib::scene
{
class SceneMetrics : public sys::IDataWrapper
{
public:
    mtps::Rectf32 currentView() const;
};
} // namespace lib::scene

#endif
