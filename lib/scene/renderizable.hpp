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

		class RenderizablePropertyGroup
		{
		public:
			Property<Color> color;
			Property<sptr<Texture>> texture;
			Property<bool> visible{ true };

			RenderizablePropertyGroup() = default;
			RenderizablePropertyGroup(Color color, sptr<Texture> texture)
				: color{ std::move(color) }, texture{ std::move(texture) } {}

			RenderizablePropertyGroup(const RenderizablePropertyGroup &) = default;
			RenderizablePropertyGroup &operator=(const RenderizablePropertyGroup &) = default;
			RenderizablePropertyGroup(RenderizablePropertyGroup &&) = default;
			RenderizablePropertyGroup &operator=(RenderizablePropertyGroup &&) = default;
		};
		class Renderizable : public core::HasName, public RenderizablePropertyGroup
		{
		public:
			Renderizable(SceneNode *const parent, const str &name, const PrimitiveType type, const u32 vertexCount);
			virtual ~Renderizable() = default;

			void render();

			Rectf32 bounds() const noexcept { return m_vertices.bounds(); }

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
			VertexArray m_vertices;
			bool m_geometryNeedsUpdate{ true };
			bool m_colorNeedsUpdate{ true };

		};
	}
}

#endif
