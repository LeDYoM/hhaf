#include <haf/scene/include/scenenodefactory.hpp>
#include <haf/scene/include/scenenode.hpp>

#include <map>

using namespace mtps;

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
        constructors_[std::move(name)] = std::move(scene_cf);
    }

    inline SceneNodeConstructorFunction get(str name)
    {
        return constructors_[std::move(name)];
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

    private_->insert(std::move(type_name),
                     std::move(scene_constructor_function));
    return true;
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
