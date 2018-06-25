#include "isimplenode.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/texture.hpp>

namespace lib::scene::nodes
{
	ISimpleNode::ISimpleNode(SceneNode *const parent, const str &name, const u32 pointCount)
		: Renderizable{ parent, name, TriangleFan, pointCount + 2 } 
	{
		textureRect.setCallback([this]() { updateTextureCoords(); });
		box.setCallback([this]() { m_geometryNeedsUpdate = true; });
	}

	void ISimpleNode::updateGeometry()
	{
		if (m_geometryNeedsUpdate) {
			m_geometryNeedsUpdate = false;
			updateGeometrySimpleNode();
            color.setChanged();
            textureRect.setChanged();
		}

        if (textureRect.readResetHasChanged()) {
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


    void nodes::ISimpleNode::setTextureAndTextureRect
    (sptr<Texture> texture_, const Rectf32& textRect)
    {
        texture.set(texture_);
        if (texture_) {
            auto tSize(texture_->size());
            textureRect = {
                static_cast<s32>(textRect.left),
                static_cast<s32>(textRect.top),
                static_cast<s32>(textRect.width),
                static_cast<s32>(textRect.height)
            };
        }
    }

    void nodes::ISimpleNode::setTextureFill(sptr<Texture> texture_)
    {
        if (texture_)
        {
            setTextureAndTextureRect(std::move(texture_),
                { 0.0f, 0.0f, static_cast<vector2df>(texture_->size()) } );
        }
    }
}
