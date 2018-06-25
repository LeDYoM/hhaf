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

            constexpr Rectf32 bounds() const noexcept { return m_vertices.bounds(); }

            PropertyState<Color> color;
            BasicProperty<bool> visible{ true };

            template <typename T>
            constexpr T *const rnCast() {
                return dynamic_cast<T *const>(this);
            }

            template <typename T>
            constexpr const T *const rnCast() const {
                return dynamic_cast<const T *const>(this);
            }

        private:
            SceneNode *m_parent;

        protected:
            virtual void updateGeometry() = 0;
            PropertyState<sptr<Texture>> texture;
            VertexArray m_vertices;
            bool m_geometryNeedsUpdate{ true };
        private:
            void updateColor();
        };
    }
}

#endif
