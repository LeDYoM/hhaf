#pragma once

#ifndef LIB_SCENE_RENDERIZABLE_INCLUDE_HPP__
#define LIB_SCENE_RENDERIZABLE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <lib/scene/transformable.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/vertexarray.hpp>
#include <lib/include/resources/itexture.hpp>

namespace lib
{
    namespace scene
    {
        class SceneNode;

        class Renderizable : public core::HasName
        {
        public:
            Renderizable(SceneNode *const parent, const str &name, const u32 vertexCount);
            virtual ~Renderizable();

            void render();

            PropertyState<Rectf32> box;

            PropertyState<Color> color;
            BasicProperty<bool> visible{ true };

            void setTextureAndTextureRect(sptr<ITexture> texture_,
                                          const Rectf32& textRect);

            void setTextureFill(sptr<ITexture> texture_);

        private:
            SceneNode *m_parent;

        protected:
            PropertyState<Rects32> textureRect;
            PropertyState<sptr<ITexture>> texture;

            VertexArray m_vertices;
        private:
            virtual void updateGeometrySimpleNode() = 0;
            void updateTextureCoords();

            void updateGeometry();
            void updateColor();
        };
    }
}

#endif
