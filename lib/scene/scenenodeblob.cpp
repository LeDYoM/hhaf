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

    const input::InputSystem & SceneNodeBlob::inputSystem() const
    {
        return sceneManager().systemProvider().inputSystem();
    }

    input::InputSystem & SceneNodeBlob::inputSystem()
    {
        return sceneManager().systemProvider().inputSystem();
    }

    const core::RandomSystem & SceneNodeBlob::randomSystem() const
    {
        return sceneManager().systemProvider().randomSystem();
    }

    core::RandomSystem & SceneNodeBlob::randomSystem()
    {
        return sceneManager().systemProvider().randomSystem();
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
