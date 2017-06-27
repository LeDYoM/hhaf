#ifndef LIB_DRAW_NODESHAPE_HPP__
#define LIB_DRAW_NODESHAPE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include "isimplenode.hpp"

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			class NodeShape : public ISimpleNode
			{
			public:
				explicit NodeShape(str &&name, const u32 pointCount);
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
