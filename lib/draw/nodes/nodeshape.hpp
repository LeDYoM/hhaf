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
				explicit NodeShape(str_const &&name, const u32 pointCount);
				virtual ~NodeShape();

				virtual void configure() override;

				Property<u32> pointCount;

			protected:
				virtual void updateGeometrySimpleNode() override;
			};
		}
	}
}

#endif
