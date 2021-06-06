#ifndef HAF_SCENE_SCENENODEFACTORY_INCLUDE_HPP
#define HAF_SCENE_SCENENODEFACTORY_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene/scene.hpp>

namespace haf::scene
{
template <typename T>
htps::uptr<T> createScene()
{
    return htps::muptr<T>();
}

class SceneNodeFactory
{
public:
    using InterfaceType                = Scene;
    using CreateReturnType             = htps::sptr<InterfaceType>;
    using SceneNodeConstructorFunction = htps::function<CreateReturnType()>;

    SceneNodeFactory();
    ~SceneNodeFactory();

    bool registerSceneNodeType(
        htps::str type_name,
        SceneNodeConstructorFunction scene_constructor_function);

    bool unregisterSceneNodeType(htps::str type_name);

    template <typename T>
    constexpr bool registerSceneNodeType(
        SceneNodeConstructorFunction scene_constructor_function)
    {
        return registerSceneNodeType(T::StaticTypeName,
                                     std::move(scene_constructor_function));
    }

    template <typename T>
    constexpr bool registerSceneNodeType(htps::str type_name)
    {
        return registerSceneNodeType(std::move(type_name), createScene<T>);
    }

    template <typename T>
    constexpr bool registerSceneNodeType()
    {
        return registerSceneNodeType(T::StaticTypeName, createScene<T>);
    }

    template <typename T>
    constexpr bool unregisterSceneNodeType()
    {
        return unregisterSceneNodeType(T::StaticTypeName);
    }

    CreateReturnType create(const htps::str& type_name);

    template <typename T>
    constexpr CreateReturnType create()
    {
        return create(T::StaticTypeName);
    }

private:
    struct SceneNodeFactoryPrivate;
    htps::uptr<SceneNodeFactoryPrivate> private_;
};
}  // namespace haf::scene

#endif
