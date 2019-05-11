#include "nodequad.hpp"
#include "geometry_math.hpp"

#include <logger/include/log.hpp>

namespace lib::scene::nodes
{

    void NodeQuad::updateGeometrySimpleNode()
	{
        constexpr size_type nPoints(4U);
        constexpr size_type nVertex(nPoints + 2);

		const Rectf32 &cBox{ box() };        
        auto& vertices(m_vertices.verticesArray());

        vertices.resize(nVertex); // + 2 for center and repeated first point
        vertices[0].position = { cBox.center().x,   cBox.center().y };
        vertices[1].position = { cBox.left,         cBox.top };
        vertices[2].position = { cBox.right(),      cBox.top };
        vertices[3].position = { cBox.right(),      cBox.bottom() };
        vertices[4].position = { cBox.left,         cBox.bottom() };
        vertices[5] = vertices[1];
	}
}
