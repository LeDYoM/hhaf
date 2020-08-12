#pragma once

#ifndef HAF_SCENE_SCENEMETRICS_VIEW_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_VIEW_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <haf/system/include/idatawrapper.hpp>

namespace haf::scene
{
class SceneMetricsView : public sys::IDataWrapper
{
public:
    mtps::Rectf32 currentView() const;
    mtps::Rectf32 currentViewPort() const;
};
}  // namespace haf::scene

#endif
