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

			virtual void draw() override;
			const sptr<Texture> &getTexture() const { return m_texture; }

			NotifableProperty<Color> color;
			ReadOnlyProperty<Rectf32> bounds;

		protected:
			void updateFillColors();
			Property<Rectf32> protectedBounds;

			VertexArray m_vertices;
			sptr<Texture> m_texture;
		private:
			Color m_color;
			Rectf32 m_bounds;
		};
	}
}

#endif
