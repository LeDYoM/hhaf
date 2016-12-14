#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "hasname.hpp"
#include "idrawable.hpp"
#include "transformable.hpp"
#include "color.hpp"
#include <lib/include/types.hpp>
#include "vertexarray.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
		class Renderizable : public core::HasName, public IDrawable, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name, PrimitiveType type, u32 vertexCount);
			virtual ~Renderizable();

			virtual void setColor(const Color color);
			inline Color color() const noexcept { return m_color; }
			Rectf32 getLocalBounds() const noexcept { return m_bounds; }
			virtual void draw() override;
			sptr<Texture> getTexture() const { return m_texture; }

		protected:
			void updateFillColors();

			VertexArray m_vertices;
			sptr<Texture> m_texture;
			Rectf32 m_bounds;
			Color m_color;
		};
	}
}

#endif
