#include "scenenodefactory.hpp"
#include "scenenode.hpp"

#include <map>

namespace lib::scene
{
    struct SceneNodeFactory::SceneNodeFactoryPrivate
    {
        std::map<str, SceneNodeConstructorFunction> constructors_;

        inline bool containsSceneType(const str& name)
        {
            return constructors_.find(name) != std::end(constructors_);
        }

        inline void insert(str name, SceneNodeConstructorFunction scene_cf)
        {
            constructors_[std::move(name)] = scene_cf;
        }

        inline SceneNodeConstructorFunction get(str name)
        {
            return constructors_[std::move(name)];
        }
    };

    SceneNodeFactory::SceneNodeFactory()
        : private_{ muptr<SceneNodeFactoryPrivate>() } {}

    SceneNodeFactory::~SceneNodeFactory() = default;

    bool SceneNodeFactory::registerSceneType(str type_name, SceneNodeConstructorFunction scene_constructor_function)
    {
        if (private_->containsSceneType(type_name))
        {
            return false;
        }

        private_->insert(std::move(type_name), std::move(scene_constructor_function));
        return true;
    }

    uptr<InterfaceType> SceneNodeFactory::create(const str &type_name)
    {
        if (!private_->containsSceneType(type_name))
        {
            return uptr<InterfaceType>(nullptr);
        }

        auto constructor(private_->get(type_name));
        if (!constructor)
        {
            return uptr<InterfaceType>(nullptr);
        }

        return constructor();
    }
}
