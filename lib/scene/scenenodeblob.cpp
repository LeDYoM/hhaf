#include "scenenodeblob.hpp"
#include "scenenodeblob.hpp"
#include "scenenodeblob.hpp"
#include "scenenodeblob.hpp"
#include "scenenode.hpp"

#include "scene.hpp"
#include "scenemanager.hpp"

#include <lib/system/systemprovider.hpp>

namespace lib::scene
{
    SceneNodeBlob::SceneNodeBlob(SceneNode & provider)
        : scene_node_{ provider } {}

    const input::InputSystem & SceneNodeBlob::inputSystem() const
    {
        return scene_node_.parentScene()->sceneManager().systemProvider().inputSystem();
    }

    input::InputSystem & SceneNodeBlob::inputSystem()
    {
        return scene_node_.parentScene()->sceneManager().systemProvider().inputSystem();
    }

    const core::RandomSystem & SceneNodeBlob::randomSystem() const
    {
        return scene_node_.parentScene()->sceneManager().systemProvider().randomSystem();
    }

    core::RandomSystem & SceneNodeBlob::randomSystem()
    {
        return scene_node_.parentScene()->sceneManager().systemProvider().randomSystem();
    }

    Rectf32 SceneNodeBlob::scenePerspective() const
    {
        return scene_node_.parentScene()->sceneManager().viewRect();
    }
}
