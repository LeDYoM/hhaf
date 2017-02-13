#ifndef LIB_DRAW_NODESHAPE_HPP__
#define LIB_DRAW_NODESHAPE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "isimplenode.hpp"

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			class NodeShape : public ISimpleNode
			{
			public:
				explicit NodeShape(str_const name, const Rectf32 &box, sptr<Texture> texture, const u32 pointCount, const Color &color);
				virtual ~NodeShape();

				Property<u32> pointCount;

			protected:
				virtual void updateGeometrySimpleNode() override;
			};
		}
	}
}

#endif
