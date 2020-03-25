#pragma once

#ifndef LIB_SCENE_SCENENODEFACTORY_INCLUDE_HPP
#define LIB_SCENE_SceneNodeFactory_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/include/scene.hpp>

namespace lib::scene
{
template <typename T>
mtps::uptr<T> createScene()
{
    return mtps::muptr<T>();
}

class SceneNodeFactory
{
public:
    using InterfaceType = Scene;
    using CreateReturnType = mtps::sptr<InterfaceType>;
    using SceneNodeConstructorFunction = mtps::function<CreateReturnType()>;

    SceneNodeFactory();
    ~SceneNodeFactory();

    bool registerSceneNodeType(mtps::str type_name, SceneNodeConstructorFunction scene_constructor_function);

    template <typename T>
    constexpr bool registerSceneNodeType(SceneNodeConstructorFunction scene_constructor_function)
    {
        return registerSceneNodeType(T::StaticTypeName, std::move(scene_constructor_function));
    }

    template <typename T>
    constexpr bool registerSceneNodeType(mtps::str type_name)
    {
        return registerSceneNodeType(std::move(type_name), createScene<T>);
    }

    template <typename T>
    constexpr bool registerSceneNodeType()
    {
        return registerSceneNodeType(T::StaticTypeName, createScene<T>);
    }

    CreateReturnType create(const mtps::str&type_name);

    template <typename T>
    constexpr CreateReturnType create()
    {
        return create(T::StaticTypeName);
    }

private:
    struct SceneNodeFactoryPrivate;
    mtps::uptr<SceneNodeFactoryPrivate> private_;
};
} // namespace lib::scene

#endif
