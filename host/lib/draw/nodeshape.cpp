#include "NodeShape.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

namespace lib
{
	namespace draw
	{
		NodeShape::NodeShape(const std::string &name, const vector2df& size, const u32 pointCount, const NodeMode mode)
			: Renderizable{ name, TriangleFan }, _mode{ mode }, m_textureRect{},
			m_size{ size }, m_pointCount{ pointCount }
		{
			updateGeometry();
		}

		NodeShape::~NodeShape() = default;

		void NodeShape::setSize(const vector2df size)
		{
			m_size = size;
			updateGeometry();
		}

		u32 NodeShape::getPointCount() const
		{
			return m_pointCount;
		}

		void NodeShape::setPointCount(const u32 numPoints)
		{
			m_pointCount = numPoints;
			updateGeometry();
		}
			
		vector2df NodeShape::getPoint(const u32 index) const
		{
			// TO DO:
			// Optimize and cache it
			switch (_mode)
			{
			default:
			case lib::draw::NodeShape::NodeMode::Shape:
			{
				vector2df m_radius{ m_size / 2.0f };
				const f64 angle = ((index * 2 * M_PI) / getPointCount()) - (M_PI_2);
				const vector2dd r{ std::cos(angle) * m_radius.x, std::sin(angle) * m_radius.y };
				return vector2df(static_cast<f32>(m_radius.x + r.x), static_cast<f32>(m_radius.y + r.y));
			}
			break;
			case lib::draw::NodeShape::NodeMode::Sprite:
			{
				__ASSERT(m_pointCount == 4, "Invalid sprite state");

				switch (index)
				{
				default:
				case 0: return vector2df(0, 0);
				case 1: return vector2df(m_size.x, 0);
				case 2: return vector2df(m_size.x, m_size.y);
				case 3: return vector2df(0, m_size.y);
				}
			}
			break;
			}
		}

		void NodeShape::setTexture(sptr<Texture> texture, bool resetSize/*=true*/, bool resetRect /*= false*/)
		{
			if (texture) {
				// Recompute the texture area if requested, or if there was no texture & rect before
				if (resetRect || (!m_texture && m_textureRect == Rects32{})) {
					setTextureRect({ 0, 0, static_cast<s32>(texture->getSize().x), static_cast<s32>(texture->getSize().y) });
				}
			}

			// Assign the new texture
			m_texture = texture;

			if (resetSize) {
				setSize({ static_cast<f32>(texture->getSize().x), static_cast<f32>(texture->getSize().y) });
			}
		}

		void NodeShape::setTextureRect(const Rects32& rect)
		{
			m_textureRect = rect;
			updateTexCoords();
		}

		Rects32 NodeShape::getTextureRect() const
		{
			return m_textureRect;
		}

		void NodeShape::updateGeometry()
		{
			if (_mode == NodeMode::Sprite) {
				m_bounds = m_vertices.generateQuad(m_size);
			} else if (_mode == NodeMode::Shape) {
				m_bounds = m_vertices.generateShape(m_size,m_pointCount);
			}

			// Color
			updateFillColors();

			// Texture coordinates
			updateTexCoords();
		}

		void NodeShape::updateTexCoords()
		{
			m_vertices.for_each_vertex([this](Vertex& v)
			{
				const f32 xratio = m_bounds.width > 0 ? (v.position.x - m_bounds.left) / m_bounds.width : 0;
				const f32 yratio = m_bounds.height > 0 ? (v.position.y - m_bounds.top) / m_bounds.height : 0;
				v.texCoords.x = m_textureRect.left + m_textureRect.width * xratio;
				v.texCoords.y = m_textureRect.top + m_textureRect.height * yratio;
			});
		}
	}
}
