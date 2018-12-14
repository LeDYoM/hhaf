#include "scenenodeblob.hpp"
#include "scenenode.hpp"

#include "scene.hpp"
#include "scenemanager.hpp"

namespace lib::scene
{
    Rectf32 SceneNodeBlob::scenePerspective()
    {
        return scene_node_.parentScene()->sceneManager().viewRect();
    }

}
