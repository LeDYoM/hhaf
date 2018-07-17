#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "transformable.hpp"
#include "color.hpp"
#include <lib/scene/hasname.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include "vertexarray.hpp"

namespace lib
{
    namespace scene
    {
        class Texture;
        class SceneNode;

        class Renderizable : public core::HasName
        {
        public:
            Renderizable(SceneNode *const parent, const str &name, const PrimitiveType type, const u32 vertexCount);
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
