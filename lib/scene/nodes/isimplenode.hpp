#ifndef LIB_DRAW_ISIMPLENODE_HPP__
#define LIB_DRAW_ISIMPLENODE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/renderizable.hpp>

namespace lib
{
	namespace scene
	{
		class Texture;
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