#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "hasname.hpp"
#include "idrawable.hpp"
#include "transformable.hpp"
#include "color.hpp"
#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>
#include "vertexarray.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
		class Renderizable : public core::HasName, public IDrawable, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name, sptr<Texture> texture, PrimitiveType type, u32 vertexCount, const Color &color);
			virtual ~Renderizable() = default;

			virtual void setColor(const Color &color);
			inline Color getColor() const noexcept { return m_color; }
			Rectf32 getLocalBounds() const noexcept { return m_bounds; }
			virtual void draw() override;
			sptr<Texture> getTexture() const { return m_texture; }

			NotifableProperty<Color> color;

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
