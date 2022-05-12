#include <haf/include/scene/scenenodefactory.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <map>

using namespace htps;

namespace haf::scene
{
struct SceneNodeFactory::SceneNodeFactoryPrivate
{
    std::map<str, SceneNodeConstructorFunction> constructors_;

    inline bool containsSceneNodeType(const str& name)
    {
        return constructors_.find(name) != std::end(constructors_);
    }

    inline void insert(str name, SceneNodeConstructorFunction scene_cf)
    {
        constructors_[htps::move(name)] = htps::move(scene_cf);
    }

    inline void erase(str name) { constructors_.erase(htps::move(name)); }

    inline SceneNodeConstructorFunction get(str name)
    {
        return constructors_[htps::move(name)];
    }
};

SceneNodeFactory::SceneNodeFactory() :
    private_{muptr<SceneNodeFactoryPrivate>()}
{}

SceneNodeFactory::~SceneNodeFactory() = default;

bool SceneNodeFactory::registerSceneNodeType(
    str type_name,
    SceneNodeConstructorFunction scene_constructor_function)
{
    if (private_->containsSceneNodeType(type_name))
    {
        return false;
    }

    private_->insert(htps::move(type_name),
                     htps::move(scene_constructor_function));
    return true;
}

bool SceneNodeFactory::unregisterSceneNodeType(htps::str type_name)
{
    if (!private_->containsSceneNodeType(type_name))
    {
        return false;
    }

    private_->erase(type_name);
    return (!private_->containsSceneNodeType(type_name));
}

SceneNodeFactory::CreateReturnType SceneNodeFactory::create(
    const str& type_name)
{
    if (!private_->containsSceneNodeType(type_name))
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
}  // namespace haf::scene
