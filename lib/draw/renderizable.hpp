#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "scenenode.hpp"
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
		class Renderizable : public SceneNode, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name, sptr<Texture> texture_, PrimitiveType type, u32 vertexCount, const Color &color_);
			virtual ~Renderizable();

			virtual void draw() override;

			Property<Color> color;

			inline Rectf32 bounds() const noexcept { return m_vertices.bounds(); }
		protected:
			Property<sptr<Texture>> texture;
			VertexArray m_vertices;
		};
	}
}

#endif
