#include "nodequad.hpp"
#include <mtypes/include/log.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			void NodeQuad::configure()
			{
				ISimpleNode::configure();
				updateGeometry();
			}

			void NodeQuad::updateGeometrySimpleNode()
			{
				constexpr u32 nPoints = 4;
				constexpr u32 nVertex = nPoints + 2;

				const Rectf32 &cBox{ box() };

				auto &vertices(m_vertices.verticesArray());

				vertices.resize(nVertex); // + 2 for center and repeated first point
				vertices[0].position = { cBox.center().x, cBox.center().y };
				vertices[1].position = { cBox.left, cBox.top };
				vertices[2].position = { cBox.right(), cBox.top };
				vertices[3].position = { cBox.right(), cBox.bottom() };
				vertices[4].position = { cBox.left, cBox.bottom() };
				vertices[5] = vertices[1];

				// Update the bounding rectangle
				m_vertices.setBounds(cBox);
			}
		}
	}
}
