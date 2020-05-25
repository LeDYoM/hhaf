#pragma once

#ifndef HAF_SCENE_SCENE_CONTROL_INCLUDE_HPP
#define HAF_SCENE_SCENE_CONTROL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene/include/scene_director.hpp>
#include <haf/system/include/idatawrapper.hpp>

namespace haf::scene
{
/**
 * @brief Class to provide access to the control of the scene.
 * This class provides methods to finish the scene and change
 * to a new one, attach a @b SceneDirectorType or finish
 * the scene management.
 */
class SceneControl : public sys::IDataWrapper
{
public:
    /**
     * @brief Method to change to the next scene.
     */
    void switchToNextScene();

    /**
     * @brief Set the Scene Director object to allow the scene
     * @b SceneManager to perform scene changes in the desired scene
     * order.
     * 
     * @param scene_director Object of the @b SceneDirectorType
     */
    void setSceneDirector(SceneDirectorType scene_director);

    /**
     * @brief Gives the control to the @b SceneController and
     * @b SceneManager to perform the main loop updating the scene.
     * 
     * @param scene_name Registered name of the scene to start
     * @return true  Everything went correct
     * @return false A problem happened.
     */
    bool startScene(const mtps::str& scene_name);

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
    void requestExit();

    /**
     * @brief Ask the system about the status of the request to finish the
     *  current aplication.
     * 
     * @return true The system will terminate at the next opportunity.
     * @return false The system has no intention of terminating the current
     *  application.
     */
    bool exitRequested() const;
};
} // namespace haf::scene

#endif
