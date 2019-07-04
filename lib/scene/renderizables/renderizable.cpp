#include "renderizable.hpp"
#include <lib/system/rendersystem.hpp>

#include <lib/scene/scenemanager.hpp>
#include <lib/scene/renderdata.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/resources/texture.hpp>
#include <lib/system/systemprovider.hpp>

#include "geometry_math.hpp"

namespace lib::scene
{
    namespace
    {
        template <typename T>
        constexpr int sgn(const T val) noexcept
        {
            return (T(0) < val) - (val < T(0));
        }

        template <typename T>
        constexpr int sgn_cos(T angle)
        {
            return sgn(std::cos(angle));
        }

        template <typename T>
        constexpr int sgn_sin(T angle) 
        {
            return sgn(std::sin(angle));
        }
    }
    Renderizable::Renderizable(SceneNode * const parent, str name, const u32 vertexCount)
        : core::HasName{ std::move(name) }, m_parent{ parent }, m_vertices{ TriangleFan, vertexCount } { }

    Renderizable::~Renderizable() = default;

    void Renderizable::render()
    {
        if (visible())
        {
            updateGeometry();

            if (!m_vertices.empty()) 
            {
                m_parent->parentScene()->sceneManager().systemProvider().renderSystem().
                        draw(scene::RenderData{
                    m_vertices,
                    m_parent->globalTransform(),
                    dynamic_cast<Texture*>(texture().get())
                });
            }
        }
    }

    void Renderizable::updateTextureCoords()
    {
        const auto& localbounds(box());
        BasicVertexArray& vertices{ m_vertices.verticesArray() };
        for (auto &v : vertices)
        {
            const f32 xratio((v.position.x - localbounds.left) / localbounds.width);
            const f32 yratio((v.position.y - localbounds.top) / localbounds.height);
            v.texCoords.x = textureRect().left + (textureRect().width * xratio);
            v.texCoords.y = textureRect().top + (textureRect().height * yratio);
        }
    }

    void Renderizable::setTextureAndTextureRect
        (sptr<ITexture> texture_, const Rectf32& textRect)
    {
        texture.set(texture_);
        if (texture_)
        {
            auto tSize(texture_->size());
            textureRect = {
                static_cast<s32>(textRect.left),
                static_cast<s32>(textRect.top),
                static_cast<s32>(textRect.width),
                static_cast<s32>(textRect.height)
            };
        }
    }

    vector2dd Renderizable::getPositionFromAngleAndRadius(const f64 angle, const vector2df& radius) const
    {
        switch (figType())
        {
            default:
            case FigType_t::Quad:
            {
                return { (sgn_cos(angle) * radius.x),
                sgn_sin(angle) * radius.y };
            }
            break;
            case FigType_t::Shape:
            {
                return { std::cos(angle) * radius.x,
                    std::sin(angle) * radius.y };
            }
        }
    }

    void Renderizable::setTextureFill(sptr<ITexture> texture_)
    {
        if (texture_)
        {
            setTextureAndTextureRect(std::move(texture_),
                { 0.0f, 0.0f, static_cast<vector2df>(texture_->size()) } );
        }
    }

    void Renderizable::updateGeometry()
    {
        if (ps_readResetHasChanged(box, figType))
        {
            updateGeometrySimpleNode();
            color.setChanged();
            textureRect.setChanged();
        }

        if (textureRect.readResetHasChanged()) 
        {
            updateTextureCoords();
            color.setChanged();
        }

        if (color.readResetHasChanged()) 
        {
            const Color c{color()};
            for (auto& v : m_vertices.verticesArray()) 
            {
                v.color = c;
            }
        }
    }

    void Renderizable::updateGeometrySimpleNode()
    {
        if (pointCount()) 
        {
            const Rectf32 &cBox{ box() };
            auto& vertices(m_vertices.verticesArray());

            const size_type nPoints{pointCount()};
            const size_type nVertex{nPoints + 2};
            const vector2df radius{ cBox.size() / 2.0f };

            vertices.resize(nVertex); // + 2 for center and repeated first point
            const f64 baseAngle(PiM2Constant<f64> / static_cast<f64>(nPoints));
            const auto leftTop(cBox.leftTop());

            for (size_type i{ 0U }; i < nPoints; ++i) 
            {
                const f64 angle{ (i * baseAngle) };
                const vector2dd r{ getPositionFromAngleAndRadius(angle, radius)  };
                vertices[i + 1].position = leftTop + radius + static_cast<vector2df>(r);
            }

            vertices[nPoints + 1].position = vertices[1].position;
            vertices[0].position = radius + leftTop;
        }
    }
}
