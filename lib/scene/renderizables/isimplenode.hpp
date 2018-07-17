#pragma once

#ifndef LIB_SCENE_ISIMPLENODE_HPP__
#define LIB_SCENE_ISIMPLENODE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/renderizable.hpp>

namespace lib::scene
{
    class Texture;
    namespace nodes
    {
        class ISimpleNode : public Renderizable
        {
        public:
            ISimpleNode(SceneNode *const parent, const str &name, const u32 pointCount);
            virtual ~ISimpleNode() {}
        };
    }
}

#endif
