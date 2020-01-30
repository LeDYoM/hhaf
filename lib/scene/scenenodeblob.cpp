#include "scenenodeblob.hpp"

#include <lib/scene/scenenode.hpp>
#include <lib/scene/scenecontroller.hpp>

#include "scene.hpp"
#include <lib/system/scenemanager.hpp>

#include <lib/resources/include/resourcemanager.hpp>
#include <lib/system/systemprovider.hpp>

#include <hosted_app/include/iapp.hpp>

#include <lib/resources_interface/include/iresourceloader.hpp>
#include <lib/resources_interface/include/iresourcehandler.hpp>

namespace lib::scene
{
SceneNodeBlob::SceneNodeBlob(SceneNode &provider,
    rptr<SceneManager> scene_manager)
    : scene_node_{provider}, scene_manager_{std::move(scene_manager)} {}

const SceneManager &SceneNodeBlob::sceneManager() const noexcept
{
    return *scene_manager_;
}

SceneManager &SceneNodeBlob::sceneManager() noexcept
{
    return *scene_manager_;
}

const SceneController &SceneNodeBlob::sceneController() const noexcept
{
    return *(sceneManager().sceneController());
}

SceneController &SceneNodeBlob::sceneController() noexcept
{
    return *(sceneManager().sceneController());
}

const sys::InputSystem &SceneNodeBlob::inputSystem() const noexcept
{
    return sceneManager().systemProvider().inputSystem();
}

sys::InputSystem &SceneNodeBlob::inputSystem() noexcept
{
    return sceneManager().systemProvider().inputSystem();
}

const sys::RandomSystem &SceneNodeBlob::randomSystem() const noexcept
{
    return sceneManager().systemProvider().randomSystem();
}

sys::RandomSystem &SceneNodeBlob::randomSystem() noexcept
{
    return sceneManager().systemProvider().randomSystem();
}

const IApp &SceneNodeBlob::app() const
{
    return sceneManager().systemProvider().app();
}

IApp &SceneNodeBlob::app()
{
    return sceneManager().systemProvider().app();
}

Rectf32 SceneNodeBlob::scenePerspective() const
{
    return sceneManager().viewRect();
}

} // namespace lib::scene
