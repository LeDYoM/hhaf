#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include "color.hpp"
#include "isimplenode.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
		class NodeShape : public ISimpleNode
		{
		public:
			explicit NodeShape(const std::string &name, const vector2df& size, const u32 pointCount);
			virtual ~NodeShape() = default;
		protected:
			virtual void updateGeometrySimpleNode() override;
		};
	}
}

#endif
