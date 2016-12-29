#include "nodequad.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		NodeQuad::NodeQuad(const std::string &name, const vector2df& size, sptr<Texture> texture, const Color &color)
			: ISimpleNode{ name, size, texture, 4,color }
		{
			updateGeometry();
		}

		void NodeQuad::updateGeometrySimpleNode()
		{
			Renderizable::bounds.set(m_vertices.generateQuad(m_size));
		}
	}
}
