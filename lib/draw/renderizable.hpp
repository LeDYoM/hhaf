#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "hasname.hpp"
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
		class Renderizable : public core::HasName, public SceneNode, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name, sptr<Texture> texture_, PrimitiveType type, u32 vertexCount, const Color &color_);
			virtual ~Renderizable() = default;

			virtual void draw() override;

			Property<Color> color;

		protected:
			Property<sptr<Texture>> texture;
			Property<Rectf32> bounds;

			void updateFillColors();
			VertexArray m_vertices;
		};
	}
}

#endif
