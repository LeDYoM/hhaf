#include "isimplenode.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/texture.hpp>

namespace lib::scene::nodes
{
	ISimpleNode::ISimpleNode(SceneNode *const parent, const str &name, const u32 pointCount)
		: Renderizable{ parent, name, TriangleFan, pointCount + 2 } 
	{
		texture.setCallback([this]()
		{
			if (texture()) {
				auto tSize(texture()->size());
				textureRect = { 0, 0, static_cast<s32>(tSize.x), static_cast<s32>(tSize.y) };
			}
		});
		textureRect.setCallback([this]() { updateTextureCoords(); });
		box.setCallback([this]() { m_geometryNeedsUpdate = true; });
	}

	void ISimpleNode::updateGeometry()
	{
		if (m_geometryNeedsUpdate) {
			m_geometryNeedsUpdate = false;
			updateGeometrySimpleNode();
			m_colorNeedsUpdate = true;
			m_textureRectNeedsUpdate = true;
		}

		if (m_colorNeedsUpdate) {
			m_colorNeedsUpdate = false;
			color.update();
		}

		if (m_textureRectNeedsUpdate) {
			m_textureRectNeedsUpdate = false;
			updateTextureCoords();
		}
	}

	void ISimpleNode::updateTextureCoords()
	{
		const Rectf32 localbounds(bounds());
		BasicVertexArray& vertices{ m_vertices.verticesArray() };
		if (!vertices.empty()) {
			for (auto &v : vertices) {
				const f32 xratio((v.position.x - localbounds.left) / localbounds.width);
				const f32 yratio((v.position.y - localbounds.top) / localbounds.height);
				v.texCoords.x = textureRect().left + (textureRect().width * xratio);
				v.texCoords.y = textureRect().top + (textureRect().height * yratio);
			}
		}
	}
}
