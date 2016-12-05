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
		class Renderizable : public core::HasName, public IDrawable, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name, PrimitiveType type, std::size_t vertexCount = 0);
			virtual ~Renderizable();

			virtual void draw() = 0;
			virtual void setColor(const Color color) = 0;

			virtual Rectf32 getLocalBounds() const;

		protected:
			VertexArray m_vertices;
			Rectf32 m_bounds;
		};
	}
}

#endif
