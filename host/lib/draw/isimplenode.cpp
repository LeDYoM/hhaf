#include "isimplenode.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace draw
	{
		ISimpleNode::ISimpleNode(const std::string &name, const vector2df& size, const u32 pointCount)
			: Renderizable{ name, TriangleFan, pointCount + 2 }, m_textureRect{}, m_size{ size }, m_pointCount{ pointCount } {}

		void ISimpleNode::setSize(const vector2df &size)
		{
			m_size = size;
			updateGeometry();
		}

		void ISimpleNode::setTexture(sptr<Texture> texture)
		{
			if (texture) {
				if ((!m_texture && m_textureRect == Rects32{})) {
					setTextureRect({ 0, 0, static_cast<s32>(texture->getSize().x), static_cast<s32>(texture->getSize().y) });
				}
			}

			setSize({ static_cast<f32>(texture->getSize().x), static_cast<f32>(texture->getSize().y) });
			m_texture = std::move(texture);
		}

		void ISimpleNode::setTextureRect(const Rects32& rect)
		{
			m_textureRect = rect;
			updateTexCoords();
		}

		Rects32 ISimpleNode::getTextureRect() const
		{
			return m_textureRect;
		}

		void ISimpleNode::updateGeometry()
		{
			updateGeometrySimpleNode();

			// Color
			updateFillColors();

			// Texture coordinates
			updateTexCoords();
		}

		void ISimpleNode::updateTexCoords()
		{
			m_vertices.for_each_vertex([this](Vertex& v)
			{
				const f32 xratio = (v.position.x - m_bounds.left) / m_bounds.width;
				const f32 yratio = (v.position.y - m_bounds.top) / m_bounds.height;
				v.texCoords.x = m_textureRect.left + (m_textureRect.width * xratio);
				v.texCoords.y = m_textureRect.top + (m_textureRect.height * yratio);
			});
		}
	}
}
