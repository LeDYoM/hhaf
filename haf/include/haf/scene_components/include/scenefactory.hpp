#ifndef HAF_SCENE_SCENE_FACTORY_INCLUDE_HPP
#define HAF_SCENE_SCENE_FACTORY_INCLUDE_HPP

#include <haf/system/include/idatawrapper.hpp>
#include <haf/scene/include/scenenodefactory.hpp>
#include <haf/scene/include/scene.hpp>

namespace haf::scene
{
/**
 * @brief Class to allow clients to register a class derived from @b Scene
 * to make the @b SceneManager system able to create instances of it.
 */
class SceneFactory : public sys::IDataWrapper
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

private:
    SceneNodeFactory& sceneNodeFactory();
};

}  // namespace haf::scene

#endif
