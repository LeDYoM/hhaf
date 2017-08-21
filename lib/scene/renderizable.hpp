#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "transformable.hpp"
#include "color.hpp"
#include <lib/scene/hasname.hpp>
#include <mtypes/include/types.hpp>
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

			virtual void configure();
			virtual void draw() const;

			Property<Color> color;
			Property<bool> visible{ true };
			inline Rectf32 bounds() const noexcept { return m_vertices.bounds(); }

			template <typename T>
			constexpr T *const rnCast() {
				return dynamic_cast<T *const>(this);
			}

			template <typename T>
			constexpr const T *const rnCast() const {
				return dynamic_cast<const T *const>(this);
			}

			Property<sptr<Texture>> texture;

		protected:
			VertexArray m_vertices;
		};
	}
}

#endif
