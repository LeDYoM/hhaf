#pragma once

#ifndef LIB_SCENE_SCENENODEFACTORY_INCLUDE_HPP
#define LIB_SCENE_SceneNodeFactory_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/scene.hpp>

namespace lib::scene
{
template <typename T>
lib::uptr<T> createScene()
{
    return lib::muptr<T>();
}

class SceneNodeFactory
{
public:
    using InterfaceType = Scene;
    using CreateReturnType = sptr<InterfaceType>;
    using SceneNodeConstructorFunction = function<CreateReturnType()>;

    SceneNodeFactory();
    ~SceneNodeFactory();

    bool registerSceneNodeType(str type_name, SceneNodeConstructorFunction scene_constructor_function);

    template <typename T>
    constexpr bool registerSceneNodeType(SceneNodeConstructorFunction scene_constructor_function)
    {
        return registerSceneNodeType(T::StaticTypeName, std::move(scene_constructor_function));
    }

    template <typename T>
    constexpr bool registerSceneNodeType(str type_name)
    {
        return registerSceneNodeType(std::move(type_name), createScene<T>);
    }

    template <typename T>
    constexpr bool registerSceneNodeType()
    {
        return registerSceneNodeType(T::StaticTypeName, createScene<T>);
    }

    CreateReturnType create(const str &type_name);

    template <typename T>
    constexpr CreateReturnType create()
    {
        return create(T::StaticTypeName);
    }

private:
    struct SceneNodeFactoryPrivate;
    uptr<SceneNodeFactoryPrivate> private_;
};
} // namespace lib::scene

#endif
