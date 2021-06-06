#ifndef HAF_SCENE_APP_INITIALIZER_INCLUDE_HPP
#define HAF_SCENE_APP_INITIALIZER_INCLUDE_HPP

#include <haf/include/system/idatawrapper.hpp>
#include <haf/include/scene/scenenodefactory.hpp>
#include <haf/include/scene/scene.hpp>

namespace haf::scene
{
class AppInitializer : public sys::IDataWrapper
{
public:
    /**
     * @brief Registed a specific type of class derived from @b Scene
     * @tparam T The type to register
     * @return true The registration was correct
     * @return false A problem happened when registering the type
     */
    template <typename T>
    bool registerSceneType()
    {
        static_assert(std::is_base_of_v<Scene, T>,
                      "The template type must be inherited from Scene");
        return sceneNodeFactory().registerSceneNodeType<T>();
    }

    /**
     * @brief Gives the control to the @b SceneController and
     * @b SceneManager to perform the main loop updating the scene.
     *
     * @param scene_name Registered name of the scene to start
     * @return true  Everything went correct
     * @return false A problem happened.
     */
    bool startScene(const htps::str& scene_name);

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

private:
    SceneNodeFactory& sceneNodeFactory();
};

}  // namespace haf::scene

#endif
