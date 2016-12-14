#include "nodequad.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		NodeQuad::NodeQuad(const std::string &name, const vector2df& size, const Color &color)
			: ISimpleNode{ name, size, 4,color }
		{
			updateGeometry();
		}

		void NodeQuad::updateGeometrySimpleNode()
		{
			m_bounds = m_vertices.generateQuad(m_size);
		}
	}
}
