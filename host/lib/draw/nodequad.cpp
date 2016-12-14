#include "nodequad.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

namespace lib
{
	namespace draw
	{
		NodeQuad::NodeQuad(const std::string &name, const vector2df& size)
			: ISimpleNode{ name, size, 4 }
		{
			updateGeometry();
		}

		void NodeQuad::updateGeometrySimpleNode()
		{
			m_bounds = m_vertices.generateQuad(m_size);
		}
	}
}
