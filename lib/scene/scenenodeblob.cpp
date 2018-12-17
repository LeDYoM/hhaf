#include "scenenodeblob.hpp"
#include "scenenodeblob.hpp"
#include "scenenodeblob.hpp"
#include "scenenodeblob.hpp"
#include "scenenode.hpp"

#include "scene.hpp"
#include "scenemanager.hpp"

#include <lib/core/host.hpp>

namespace lib::scene
{
    SceneNodeBlob::SceneNodeBlob(SceneNode & provider)
        : scene_node_{ provider } {}


    const core::Host& SceneNodeBlob::host() const
    {
        return scene_node_.parentScene()->sceneManager().host();
    }

    core::Host& SceneNodeBlob::host()
    {
        return scene_node_.parentScene()->sceneManager().host();
    }

    const input::InputSystem & SceneNodeBlob::inputSystem() const
    {
        return scene_node_.parentScene()->sceneManager().host().inputSystem();
    }

    input::InputSystem & SceneNodeBlob::inputSystem()
    {
        return scene_node_.parentScene()->sceneManager().host().inputSystem();
    }

    const core::RandomSystem & SceneNodeBlob::randomSystem() const
    {
        return scene_node_.parentScene()->sceneManager().host().randomSystem();
    }

    core::RandomSystem & SceneNodeBlob::randomSystem()
    {
        return scene_node_.parentScene()->sceneManager().host().randomSystem();
    }

    Rectf32 SceneNodeBlob::scenePerspective() const
    {
        return scene_node_.parentScene()->sceneManager().viewRect();
    }
}
