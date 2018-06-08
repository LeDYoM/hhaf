#pragma once

#ifndef LIB_SCENE_GEOMETRY_INCLUDE_HPP
#define LIB_SCENE_GEOMETRY_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/include/core/log.hpp>

#include <lib/scene/vertexarray.hpp>
#include <lib/scene/vertex.hpp>

namespace lib::scene
{
    class GeometryGenerator final
    {
    public:
        using vector_type = vector2df;

        template <typename T>
        static constexpr T PiConstant = 3.14159265358979323846;
        template <typename T>
        static constexpr T PiD2Constant = PiConstant<T> / static_cast<T>(2);

        constexpr GeometryGenerator(VertexArray &vertexArray) noexcept
            : m_verticesArray{ vertexArray } {}

        constexpr void resetIndex() noexcept { m_index = 0U; }

        constexpr void addQuad(const Rectf32& box, const Rectf32& textureRect)
        {
            constexpr u32 nPoints = 4;
            constexpr u32 nVertex = nPoints + 2;
            auto& vertices(m_verticesArray.verticesArray());

            vertices.resize(nVertex); // + 2 for center and repeated first point
            vertices[0].position = { box.center().x, box.center().y };
            updateTextureVertex(vertices[0], box, textureRect);
            vertices[1].position = { box.left, box.top };
            updateTextureVertex(vertices[1], box, textureRect);
            vertices[2].position = { box.right(), box.top };
            updateTextureVertex(vertices[2], box, textureRect);
            vertices[3].position = { box.right(), box.bottom() };
            updateTextureVertex(vertices[3], box, textureRect);
            vertices[4].position = { box.left, box.bottom() };
            updateTextureVertex(vertices[4], box, textureRect);
            vertices[5] = vertices[1];
            updateTextureVertex(vertices[5], box, textureRect);

            m_index = 6;
        }

        constexpr void addShape(const Rectf32& box, const size_type nPoints, 
            const Rectf32& textureRect)
        {
            if (nPoints) {
                auto& vertices(m_verticesArray.verticesArray());

                const u32 nVertex(nPoints + 2);

                const vector2df size{ box.size() };
                const vector2df radius{ size / 2.0f };

                vertices.resize(nVertex); // + 2 for center and repeated first point
                const f64 baseAngle((2 * PiConstant<f64>) / static_cast<f64>(nPoints));
                const auto leftTop(box.leftTop());
                for (u32 i{ 0 }; i < nPoints; ++i) {
                    const f64 angle{ (i*baseAngle) - (GeometryGenerator::PiD2Constant<f64>) };
                    const vector2dd r{ std::cos(angle) * radius.x, std::sin(angle) * radius.y };
                    auto& vertex(vertices[i + 1]);
                    vertex.position = { static_cast<f32>(radius.x + r.x), static_cast<f32>(radius.y + r.y) };
                    vertex.position += leftTop;

                    updateTextureVertex(vertex, box, textureRect);
                }

                vertices[nPoints + 1].position = vertices[1].position;
                vertices[0].position = (box.size() / 2) + leftTop;
            }
        }

        constexpr vector2df textureVertex(const vector2df &position, 
            const Rectf32 &box, const Rectf32 &textureRect) noexcept 
        {
            const f32 xratio((position.x - box.left) / box.width);
            const f32 yratio((position.y - box.top) / box.height);
            return { textureRect.left + (textureRect.width * xratio),
                textureRect.top + (textureRect.height * yratio) };
        }

        constexpr void updateTextureVertex(Vertex &v,
            const Rectf32 &box, const Rectf32 &textureRect) noexcept
        {
            v.texCoords = textureVertex(v.position, box, textureRect);
        }

        //TO DO: Just experiment to maintain compatibility
        constexpr void addQuad2(const Rectf32& box, const Rectf32 textureUV)
        {
            auto& vertices(m_verticesArray.verticesArray());

            vertices.emplace_back(vector2df{ box.left, box.top }, vector2df{ textureUV.left, textureUV.top });
            vertices.emplace_back(vector2df{ box.right(), box.top }, vector2df{ textureUV.right(), textureUV.top });
            vertices.emplace_back(vector2df{ box.left,  box.bottom() }, vector2df{ textureUV.left, textureUV.bottom() });
            vertices.emplace_back(vector2df{ box.left,  box.bottom() }, vector2df{ textureUV.left, textureUV.bottom() });
            vertices.emplace_back(vector2df{ box.right(), box.top }, vector2df{ textureUV.right(), textureUV.top });
            vertices.emplace_back(vector2df{ box.right(), box.bottom() }, vector2df{ textureUV.right(), textureUV.bottom() });
        }

    private:
        size_type m_index{ 0U };
        VertexArray &m_verticesArray;
    };
}

#endif
