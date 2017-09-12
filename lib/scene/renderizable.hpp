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
			virtual ~Renderizable() = default;

			void render();

			Property<Color> color;
			Property<sptr<Texture>> texture;
			Property<bool> visible{ true };

			Rectf32 bounds() const noexcept { return m_vertices.bounds(); }

			template <typename T>
			constexpr T *const rnCast() {
				return dynamic_cast<T *const>(this);
			}

			template <typename T>
			constexpr const T *const rnCast() const {
				return dynamic_cast<const T *const>(this);
			}

		protected:
			virtual void updateGeometry() = 0;
			VertexArray m_vertices;
			bool m_geometryNeedsUpdate{ true };
			bool m_colorNeedsUpdate{ true };

		private:
			SceneNode *m_parent{ nullptr };
		};
	}
}

#endif
