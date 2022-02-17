#ifndef HAF_SCENE_SCENEMANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENEMANAGER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <haf/include/types/scene_types.hpp>
#include <haf/include/scene_components/iscene_control.hpp>
#include <haf/include/scene_components/iapp_initializer.hpp>
#include <haf/include/scene_components/iapp_finisher.hpp>
#include "system/system_base.hpp"

namespace haf::scene
{
class SceneController;
class SceneNode;
class SceneFactory;
}  // namespace haf::scene

namespace haf::scene
{
class HAF_PRIVATE SceneManager final : public sys::SystemBase,
                                       public ISceneControl,
                                       public IAppInitializer,
                                       public IAppFinisher
{
public:
    explicit SceneManager(sys::SystemProvider& system_provider);
    ~SceneManager() override;

    void start();
    void update();
    void finish();

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

    SceneNodeFactory& sceneNodeFactory() override;

    bool setNextApp(htps::str const& next_app) override;

private:
    htps::sptr<SceneController> scene_controller_;
};
}  // namespace haf::scene

#endif
