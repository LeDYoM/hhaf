#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "transformable.hpp"
#include "color.hpp"
#include <lib/draw/hasname.hpp>
#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>
#include "vertexarray.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
		class Renderizable : public core::HasName
		{
		public:
			explicit Renderizable(const std::string &name, sptr<Texture> texture_, PrimitiveType type, u32 vertexCount, const Color &color_);
			virtual ~Renderizable();

			virtual void draw();

			Property<Color> color;

			inline Rectf32 bounds() const noexcept { return m_vertices.bounds(); }

			inline bool isVisible() const noexcept { return m_visible; }
			inline void setVisible(bool nv) noexcept { m_visible = nv; }

			Property<vector2df> position;

			inline void move(const vector2df &offset)  noexcept { m_vertices.move(offset); }
			inline void moveX(const f32 xOffset)  noexcept { m_vertices.moveX(xOffset); }
			inline void moveY(const f32 yOffset)  noexcept { m_vertices.moveY(yOffset); }

		protected:
			bool m_visible{ true };
			Property<sptr<Texture>> texture;
			VertexArray m_vertices;
		};
	}
}

#endif
