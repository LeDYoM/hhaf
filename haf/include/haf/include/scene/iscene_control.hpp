HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_ISCENE_CONTROL_INCLUDE_HPP
#define HAF_SCENE_ISCENE_CONTROL_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::scene
{
/**
 * @brief Class to provide access to the control of the scene.
 * This class provides methods to finish the scene and change
 * to a new one, overload the appropiate function in @b Scene
 * the scene management.
 */
class ISceneControl
{
protected:
    virtual ~ISceneControl() = default;

public:
    /**
     * @brief Method to change to the next scene.
     */
    virtual void switchToNextScene() = 0;

    /**
     * @brief Gives the control to the @b SceneController and
     * @b SceneManager to perform the main loop updating the scene.
     *
     * @param scene_name Registered name of the scene to start
     * @return true  Everything went correct
     * @return false A problem happened.
     */
    virtual bool startScene(const htps::str& scene_name) = 0;

    /**
     * @brief Gives the control to the @b SceneController and
     * @b SceneManager to perform the main loop updating the scene.
     *
     * @tparam T Type of the scene to start
     * @return true  Everything went correct
     * @return false A problem happened.
     */
    template <typename T>
    inline bool startScene()
    {
        return startScene(T::StaticTypeName);
    }

    /**
     * @brief Tell the system to stop the current aplication.
     */
    virtual void requestExit() = 0;

    /**
     * @brief Ask the system about the status of the request to finish the
     *  current aplication.
     *
     * @return true The system will terminate at the next opportunity.
     * @return false The system has no intention of terminating the current
     *  application.
     */
    virtual bool exitRequested() const = 0;
};

}  // namespace haf::scene

#endif
