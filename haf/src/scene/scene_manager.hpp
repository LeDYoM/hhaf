#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <haf/include/scene_components/iscene_metrics.hpp>
#include <haf/include/scene_components/iscene_metrics_view.hpp>
#include <haf/include/scene_components/iscene_control.hpp>
#include "system/system_base.hpp"

namespace haf::scene
{
class SceneController;
class SceneNode;
}  // namespace haf::scene

namespace haf::scene
{
class SceneManager final : public sys::SystemBase,
                           public ISceneMetrics,
                           public ISceneControl
{
public:
    explicit SceneManager(sys::SystemProvider& system_provider);
    ~SceneManager();

    void start();
    void update();
    void finish();

    SceneBox currentView() const override;
    SceneBox currentViewPort() const override;
    void setViewPort(SceneBox const& vp) override;
    void setViewRect(SceneBox const& vr) override;
    void move(SceneCoordinates const& delta) override;

    htps::sptr<SceneController const> sceneController() const noexcept;
    htps::sptr<SceneController> sceneController() noexcept;

    /**
     * @brief Method to change to the next scene.
     */
    void switchToNextScene() override;

    /**
     * @brief Gives the control to the @b SceneController and
     * @b SceneManager to perform the main loop updating the scene.
     *
     * @param scene_name Registered name of the scene to start
     * @return true  Everything went correct
     * @return false A problem happened.
     */
    bool startScene(const htps::str& scene_name) override;

    /**
     * @brief Tell the system to stop the current aplication.
     */
    void requestExit() override;

    /**
     * @brief Ask the system about the status of the request to finish the
     *  current aplication.
     *
     * @return true The system will terminate at the next opportunity.
     * @return false The system has no intention of terminating the current
     *  application.
     */
    bool exitRequested() const override;

private:
    htps::sptr<SceneController> scene_controller_;
};
}  // namespace haf::scene

#endif
