#pragma once

#ifndef LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_BLOBL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

namespace lib::scene
{
    class SceneNode;

    class SceneNodeBlob
    {
    public:
        SceneNodeBlob(SceneNode& sibling_node)
            : scene_node_{ sibling_node } {}

        Rectf32 scenePerspective();

    private:
        SceneNode& scene_node_;
    };
}

#endif
