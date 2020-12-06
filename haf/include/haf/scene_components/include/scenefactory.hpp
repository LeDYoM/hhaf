#ifndef HAF_SCENE_SCENE_FACTORY_INCLUDE_HPP
#define HAF_SCENE_SCENE_FACTORY_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/function.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/scene/include/scenenodefactory.hpp>

namespace haf::scene
{

class SceneFactory : public sys::IDataWrapper
{
public:
    template <typename T>
    bool registerSceneType()
    {
        return sceneNodeFactory().registerSceneNodeType<T>();
    }

private:
    SceneNodeFactory& sceneNodeFactory();
};

}  // namespace haf::scene

#endif
