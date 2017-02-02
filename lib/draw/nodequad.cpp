#include "nodequad.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		NodeQuad::NodeQuad(const std::string &name, const vector2df& size, sptr<Texture> texture, const Color &color)
			: ISimpleNode{ name, size, texture, 4,color }
		{
			logConstruct("Name: ", name);

			updateGeometry();
		}

		NodeQuad::~NodeQuad()
		{
			logDestruct("Name: ", name());
		}

		void NodeQuad::updateGeometrySimpleNode()
		{
//			Renderizable::bounds.set(m_vertices.generateQuad(size()));

			constexpr u32 nPoints = 4;
			constexpr u32 nVertex = nPoints + 2;

			auto &vertices(m_vertices.verticesArray());

			vertices.resize(nVertex); // + 2 for center and repeated first point
			vertices[0].position = { size().x / 2, size().y / 2 };
			vertices[1].position = { 0, 0 };
			vertices[2].position = vector2df(size().x, 0);
			vertices[3].position = vector2df(size().x, size().y);
			vertices[4].position = vector2df(0, size().y);
			vertices[5] = vertices[1];

			// Update the bounding rectangle
			m_vertices.setBounds({ 0,0, size().x, size().y });
		}
	}
}
