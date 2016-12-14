#include "nodeshape.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

#include <math.h>

namespace lib
{
	namespace draw
	{
		NodeShape::NodeShape(const std::string &name, const vector2df& size, const u32 pointCount)
			: ISimpleNode{ name, size, pointCount }
		{
			updateGeometry();
		}

		void NodeShape::updateGeometrySimpleNode()
		{
			m_bounds = m_vertices.generateShape(m_size, m_pointCount);
		}
	}
}
