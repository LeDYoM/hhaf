#include "isimplenode.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace draw
	{
		ISimpleNode::ISimpleNode(const std::string &name, const vector2df& _size, sptr<Texture> t, const u32 pointCount, const Color &color)
			: Renderizable{ name, t, TriangleFan, pointCount + 2, color },
			textureRect{ {{},{}, t ? static_cast<s32>(t->getSize().x) : 0, t ? static_cast<s32>(t->getSize().y) : 0}, [this](auto) { updateTexCoords(); } },
			size{ _size,[this](const vector2df&) { updateGeometry(); } },
			bounds{ Renderizable::bounds }
		{
			texture.setCallback([this](const auto &t)
			{
				if (t) {
					auto tSize(t->getSize());
					if ((!t.get() && textureRect() == Rects32{})) {
						textureRect = { 0, 0, static_cast<s32>(tSize.x), static_cast<s32>(tSize.y) };
					}
					size = { static_cast<f32>(tSize.x), static_cast<f32>(tSize.y) };
				}
			});
		}

		void ISimpleNode::updateGeometry()
		{
			updateGeometrySimpleNode();

			color.update();

			// Texture coordinates
			updateTexCoords();
		}

		void ISimpleNode::updateTexCoords()
		{
			m_vertices.for_each_vertex([this](Vertex& v)
			{
				const f32 xratio((v.position.x - bounds().left) / bounds().width);
				const f32 yratio((v.position.y - bounds().top) / bounds().height);
				v.texCoords.x = textureRect().left + (textureRect().width * xratio);
				v.texCoords.y = textureRect().top + (textureRect().height * yratio);
			});
		}
	}
}
