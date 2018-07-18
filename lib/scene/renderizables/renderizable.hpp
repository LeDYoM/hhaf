#pragma once

#ifndef LIB_SCENE_RENDERIZABLE_INCLUDE_HPP__
#define LIB_SCENE_RENDERIZABLE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <lib/scene/transformable.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/vertexarray.hpp>

namespace lib
{
    namespace scene
    {
        class Texture;
        class SceneNode;

        class Renderizable : public core::HasName
        {
        public:
            Renderizable(SceneNode *const parent, const str &name, const u32 vertexCount);
            virtual ~Renderizable();

            void render();

            PropertyTrigger<Rectf32> box;

            PropertyState<Color> color;
            BasicProperty<bool> visible{ true };

            void setTextureAndTextureRect(sptr<Texture> texture_,
                                          const Rectf32& textRect);

            void setTextureFill(sptr<Texture> texture_);

        private:
            SceneNode *m_parent;

        protected:
            PropertyState<Rects32> textureRect;
            PropertyState<sptr<Texture>> texture;

            VertexArray m_vertices;
            bool m_geometryNeedsUpdate{ true };
        private:
            virtual void updateGeometrySimpleNode() = 0;
            void updateTextureCoords();

            void updateGeometry();
            void updateColor();
        };
    }
}

#endif
