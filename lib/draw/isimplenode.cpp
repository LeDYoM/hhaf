#include "isimplenode.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace draw
	{
		ISimpleNode::ISimpleNode(const std::string &name, const vector2df& _size, sptr<Texture> t, const u32 pointCount, const Color &color)
			: Renderizable{ name, t, TriangleFan, pointCount + 2, color },
			m_textureRect{ {},{}, t ? static_cast<s32>(t->getSize().x) : 0, t ? static_cast<s32>(t->getSize().y) : 0 },
			size{ _size,[this](const vector2df&) { updateGeometry(); } },
			m_pointCount{ pointCount }, bounds{ Renderizable::bounds }
		{
			texture.setCallback([this](const auto &t)
			{
				if (t) {
					auto tSize(t->getSize());
					if ((!t.get() && m_textureRect == Rects32{})) {
						setTextureRect({ 0, 0, static_cast<s32>(tSize.x), static_cast<s32>(tSize.y) });
					}
					size = { static_cast<f32>(tSize.x), static_cast<f32>(tSize.y) };
				}
			});
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
				const f32 xratio((v.position.x - bounds.get().left) / bounds.get().width);
				const f32 yratio((v.position.y - bounds.get().top) / bounds.get().height);
				v.texCoords.x = m_textureRect.left + (m_textureRect.width * xratio);
				v.texCoords.y = m_textureRect.top + (m_textureRect.height * yratio);
			});
		}
	}
}
