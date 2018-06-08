#include "nodequad.hpp"

#include <lib/scene/geometry.hpp>
#include <lib/include/core/log.hpp>

namespace lib::scene::nodes
{
	void NodeQuad::updateGeometrySimpleNode()
	{
		const Rectf32 &cBox{ box() };
        GeometryGenerator geometry_generator(m_vertices);
        geometry_generator.addQuad(box(),textureRect());

		// Update the bounding rectangle
		m_vertices.bounds = cBox;
	}
}
