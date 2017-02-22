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
				ISimpleNode(str_const &&name, const u32 pointCount);
				virtual ~ISimpleNode() = default;

				virtual void configure() override;
				Property<Rectf32> box;
				Property<Rects32> textureRect;
				ForwardProperty<sptr<Texture>> texture;

			protected:
				void updateGeometry();
				void updateTextureCoords();

				virtual void updateGeometrySimpleNode() = 0;
			};
		}
	}
}

#endif
