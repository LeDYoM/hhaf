#include "isimplenode.hpp"
#include <lib/core/log.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace draw
	{
		ISimpleNode::ISimpleNode(const std::string &name, const vector2df& _size, sptr<Texture> t, const u32 pointCount, const Color &color)
			: Renderizable{ name, t, TriangleFan, pointCount + 2, color },
			textureRect{ {{},{}, t ? static_cast<s32>(t->size().x) : 0, t ? static_cast<s32>(t->size().y) : 0}, 
				[this]() { updateTextureCoords(); } },
			size{ _size,[this]() { updateGeometry(); } }
		{
			texture.setCallback([this]()
			{
				if (texture()) {
					auto tSize(texture()->size());
					if ((!texture().get() && textureRect() == Rects32{})) {
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
			updateTextureCoords();
		}

		void ISimpleNode::updateTextureCoords()
		{
			const Rectf32 bounds(bounds());
			BasicVertexArray& vertices{ m_vertices.verticesArray() };
			if (!vertices.empty()) {
				for (auto &v : vertices) {
					const f32 xratio((v.position.x - bounds.left) / bounds.width);
					const f32 yratio((v.position.y - bounds.top) / bounds.height);
					v.texCoords.x = textureRect().left + (textureRect().width * xratio);
					v.texCoords.y = textureRect().top + (textureRect().height * yratio);
				}
			}
		}
	}
}
