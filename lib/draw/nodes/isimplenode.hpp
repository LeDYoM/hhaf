#ifndef LIB_DRAW_ISIMPLENODE_HPP__
#define LIB_DRAW_ISIMPLENODE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/draw/color.hpp>
#include <lib/draw/renderizable.hpp>

namespace lib
{
	namespace draw
	{
		class Texture;
		namespace nodes
		{
			class ISimpleNode : public Renderizable
			{
			public:
				ISimpleNode(str_const &&name, const Rectf32 &box, sptr<Texture> texture, const u32 pointCount, const Color &color);
				virtual ~ISimpleNode() = default;

				Property<Rectf32> box;
				Property<Rects32> textureRect;

			protected:
				void updateGeometry();
				void updateTextureCoords();

				virtual void updateGeometrySimpleNode() = 0;
			};
		}
	}
}

#endif
