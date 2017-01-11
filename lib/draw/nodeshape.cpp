#include "nodeshape.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace draw
	{
		NodeShape::NodeShape(const std::string &name, const vector2df& size, sptr<Texture> texture, const u32 pointCount, const Color &color)
			: ISimpleNode{ name, size, texture, pointCount, color }
		{
			updateGeometry();
		}

		void NodeShape::updateGeometrySimpleNode()
		{
			Renderizable::bounds.set(m_vertices.generateShape(m_size, m_pointCount));
		}
	}
}