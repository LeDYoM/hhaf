#include "renderizable.hpp"
#include <lib/core/host.hpp>
#include <lib/system/window.hpp>
#include <lib/system/rendertarget.hpp>

#include <lib/scene/scenemanager.hpp>
#include <lib/scene/renderdata.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/resources/texture.hpp>

namespace lib::scene
{
    Renderizable::Renderizable(SceneNode * const parent, const str & name, const u32 vertexCount)
        : core::HasName{ name }, m_parent{ parent }, m_vertices{ TriangleFan, vertexCount }
    {
        box.setCallback([this]() { m_geometryNeedsUpdate = true; });
        textureRect.setCallback([this]() { updateTextureCoords(); });
    }

    Renderizable::~Renderizable() = default;

    void Renderizable::render()
    {
        if (visible()) {
            updateGeometry();

            if (!m_vertices.empty()) {

                if (color.readResetHasChanged()) {
                    updateColor();
                }

                m_parent->parentScene()->sceneManager().systemProvider().parentWindow().renderTarget()->
                        draw({
                    m_vertices,
                    m_parent->globalTransform(),
                    texture().get()
                });
            }
        }
    }

    void Renderizable::updateColor()
    {
        const Color c{color()};
        if (!m_vertices.empty()) {
            for (auto& v : m_vertices.verticesArray()) {
                v.color = c;
            }
        }
    }

    void Renderizable::updateTextureCoords()
    {
        const auto& localbounds(box());
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

    void Renderizable::setTextureAndTextureRect
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

    void Renderizable::setTextureFill(sptr<Texture> texture_)
    {
        if (texture_)
        {
            setTextureAndTextureRect(std::move(texture_),
                { 0.0f, 0.0f, static_cast<vector2df>(texture_->size()) } );
        }
    }

    void Renderizable::updateGeometry()
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
}
