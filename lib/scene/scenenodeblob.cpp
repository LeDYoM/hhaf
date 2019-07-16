#include "scenenodeblob.hpp"
#include "scenenode.hpp"

#include "scene.hpp"
#include "scenemanager.hpp"

#include <lib/system/systemprovider.hpp>
#include <lib/include/iapp.hpp>

namespace lib::scene
{
    SceneNodeBlob::SceneNodeBlob(SceneNode & provider)
        : scene_node_{ provider } {}

    const SceneManager &SceneNodeBlob::sceneManager() const noexcept
    {
        return scene_node_.parentScene()->sceneManager();
    }

    SceneManager &SceneNodeBlob::sceneManager() noexcept
    {
        return scene_node_.parentScene()->sceneManager();
    }

    const input::InputSystem & SceneNodeBlob::inputSystem() const noexcept
    {
        return sceneManager().systemProvider().inputSystem();
    }

    input::InputSystem & SceneNodeBlob::inputSystem() noexcept
    {
        return sceneManager().systemProvider().inputSystem();
    }

    const core::RandomSystem & SceneNodeBlob::randomSystem() const noexcept
    {
        return sceneManager().systemProvider().randomSystem();
    }

    core::RandomSystem & SceneNodeBlob::randomSystem() noexcept
    {
        return sceneManager().systemProvider().randomSystem();
    }

    const core::ISimulableDataProvider & SceneNodeBlob::simulableDataProvider() const noexcept
    {
        return sceneManager().systemProvider().simulableDataProvider();
    }

    core::ISimulableDataProvider & SceneNodeBlob::simulableDataProvider() noexcept
    {
        return sceneManager().systemProvider().simulableDataProvider();
    }

    const IApp& SceneNodeBlob::app() const
    {
        return sceneManager().systemProvider().app();
    }

    IApp& SceneNodeBlob::app()
    {
        return sceneManager().systemProvider().app();
    }

    Rectf32 SceneNodeBlob::scenePerspective() const
    {
        return sceneManager().viewRect();
    }
}
