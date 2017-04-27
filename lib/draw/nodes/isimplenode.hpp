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
		class TextureV1;
		namespace nodes
		{
			class ISimpleNode : public Renderizable
			{
			public:
				ISimpleNode(str &&name, const u32 pointCount);
				virtual ~ISimpleNode() = default;

				Property<Rectf32> box;
				Property<Rects32> textureRect;

			protected:
				void configureBase();
				void updateGeometry();
				void updateTextureCoords();

				virtual void updateGeometrySimpleNode() = 0;
			};
		}
	}
}

#endif
