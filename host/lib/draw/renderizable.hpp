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
			explicit Renderizable(const std::string &name, sptr<Texture> texture_, PrimitiveType type, u32 vertexCount, const Color &color_);
			virtual ~Renderizable() = default;

			virtual void draw() override;

			Property<Color> color;
			Property<Rectf32> bounds;
			Property<sptr<Texture>> texture;

		protected:
			void updateFillColors();
			VertexArray m_vertices;

		private:
			Rectf32 m_bounds;
		};
	}
}

#endif
