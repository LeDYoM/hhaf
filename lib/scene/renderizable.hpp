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
		class SceneNode;
		class Renderizable : public core::HasName
		{
		public:
			Renderizable(SceneNode *const parent, const str &name, const PrimitiveType type, const u32 vertexCount)
				: core::HasName{ name }, m_parent{ parent }, m_vertices{ type, vertexCount }, color{} {}

			virtual ~Renderizable() = default;

			virtual void configure();
			void draw() const;

			Property<Color> color;
			Property<sptr<Texture>> texture;
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

		protected:
			VertexArray m_vertices;
		private:
			SceneNode *m_parent{ nullptr };
		};
	}
}

#endif
