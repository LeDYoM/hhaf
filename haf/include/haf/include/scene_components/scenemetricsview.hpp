#ifndef HAF_SCENE_SCENEMETRICS_VIEW_INCLUDE_HPP
#define HAF_SCENE_SCENEMETRICS_VIEW_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/system/idatawrapper.hpp>

namespace haf::scene
{
/**
 * @brief Interface class to read some metrics of the current set
 * @b Scene
 */
class SceneMetricsView : public sys::IDataWrapper
{
    using BaseClass                              = sys::IDataWrapper;
    static constexpr char const StaticTypeName[] = "SceneMetricsView";

public:
    /**
     * @brief Get the current view set for the Scene
     * @return SceneBox containing the view
     */
    SceneBox currentView() const;

    /**
     * @brief Get The current Viewport of the Scene
     * @return SceneBox Containing the view port
     */
    SceneBox currentViewPort() const;
};

}  // namespace haf::scene

#endif
