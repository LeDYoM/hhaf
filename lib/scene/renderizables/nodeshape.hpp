#pragma once

#ifndef LIB_SCENE_NODESHAPE_INCLUDE_HPP__
#define LIB_SCENE_NODESHAPE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/scene/renderizables/renderizable.hpp>

namespace lib
{
    namespace scene
    {
        namespace nodes
        {
            class NodeShape : public Renderizable
            {
            public:
                explicit NodeShape(SceneNode *const parent, const str &name, const u32 pointC = 30)
                    : Renderizable{ parent, name, pointC }
                    {
                        pointCount.set(pointC + 2U);
                    }

                virtual ~NodeShape() = default;

            protected:
                virtual void updateGeometrySimpleNode() override;
            };
        }
    }
}

#endif
