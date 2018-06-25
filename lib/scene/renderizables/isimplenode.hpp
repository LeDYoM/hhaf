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

            PropertyTrigger<Rectf32> box;
            PropertyState<Rects32> textureRect;

            void setTextureAndTextureRect(sptr<Texture> texture_,
                                          const Rectf32& textRect);

            void setTextureFill(sptr<Texture> texture_);
        protected:
            void updateGeometry();
            void updateTextureCoords();

            virtual void updateGeometrySimpleNode() = 0;
        };
    }
}

#endif
