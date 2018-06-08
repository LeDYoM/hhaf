#include "nodeshape.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/geometry.hpp>
#include <lib/scene/texture.hpp>

#include <cmath>

namespace lib::scene::nodes
{
	void NodeShape::updateGeometrySimpleNode()
	{
        const Rectf32 &cBox{ box() };
        GeometryGenerator geometry_generator(m_vertices);
        geometry_generator.addShape(cBox, pointCount(), textureRect());

        // Update the bounding rectangle
        m_vertices.bounds = cBox;
	}
}
