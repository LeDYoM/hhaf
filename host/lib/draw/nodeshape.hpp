#ifndef LIB_DRAW_NODESHAPE_HPP__
#define LIB_DRAW_NODESHAPE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "isimplenode.hpp"

namespace lib
{
	namespace draw
	{
		class NodeShape : public ISimpleNode
		{
		public:
			explicit NodeShape(const std::string &name, const vector2df& size, const u32 pointCount, const Color &color);
			virtual ~NodeShape() = default;
		protected:
			virtual void updateGeometrySimpleNode() override;
		};
	}
}

#endif
