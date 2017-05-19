#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "transformable.hpp"
#include "color.hpp"
#include <lib/scene/hasname.hpp>
#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>
#include "vertexarray.hpp"

namespace lib
{
	namespace scene
	{
		class Texture;
		class Renderizable : public core::HasName
		{
		public:
			explicit Renderizable(str &&name, PrimitiveType type, u32 vertexCount);
			virtual ~Renderizable();

			void configureBase();
			virtual void configure() = 0;
			virtual void draw();

			Property<Color> color;
			Property<bool> visible{ true };
			inline Rectf32 bounds() const noexcept { return m_vertices.bounds(); }

			inline void move(const vector2df &offset)  noexcept { m_vertices.move(offset); }
			inline void moveX(const f32 xOffset)  noexcept { m_vertices.moveX(xOffset); }
			inline void moveY(const f32 yOffset)  noexcept { m_vertices.moveY(yOffset); }

			template <typename T>
			inline T *const rnCast() {
				return dynamic_cast<T *const>(this);
			}

			template <typename T>
			inline const T *const rnCast() const {
				return dynamic_cast<const T *const>(this);
			}

			Property<sptr<Texture>> texture;

		protected:
			VertexArray m_vertices;
		};
	}
}

#endif
