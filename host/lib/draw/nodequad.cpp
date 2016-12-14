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
			: Renderizable{ name, TriangleFan }, m_textureRect{},
			m_size{ size }
		{
			updateGeometry();
		}

		void NodeQuad::setSize(const vector2df size)
		{
			m_size = size;
			updateGeometry();
		}

		void NodeQuad::setTexture(sptr<Texture> texture)
		{
			if (texture) {
				// Recompute the texture area if requested, or if there was no texture & rect before
				if ((!m_texture && m_textureRect == Rects32{})) {
					setTextureRect({ 0, 0, static_cast<s32>(texture->getSize().x), static_cast<s32>(texture->getSize().y) });
				}
			}

			// Assign the new texture
			m_texture = texture;

			setSize({ static_cast<f32>(texture->getSize().x), static_cast<f32>(texture->getSize().y) });
		}

		void NodeQuad::setTextureRect(const Rects32& rect)
		{
			m_textureRect = rect;
			updateTexCoords();
		}

		Rects32 NodeQuad::getTextureRect() const
		{
			return m_textureRect;
		}

		void NodeQuad::updateGeometry()
		{
			m_bounds = m_vertices.generateQuad(m_size);

			// Color
			updateFillColors();

			// Texture coordinates
			updateTexCoords();
		}

		void NodeQuad::updateTexCoords()
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
