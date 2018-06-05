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

        constexpr GeometryGenerator(vector<Vertex> &vertexArray) noexcept
            : m_vertices{ vertexArray } {}

        constexpr void resetIndex() noexcept { m_index = 0U; }

        constexpr void addQuad(const Rectf32& box) 
        {
            constexpr u32 nPoints = 4;
            constexpr u32 nVertex = nPoints + 2;

            m_vertices.resize(nVertex); // + 2 for center and repeated first point
            m_vertices[0].position = { box.center().x, box.center().y };
            m_vertices[1].position = { box.left, box.top };
            m_vertices[2].position = { box.right(), box.top };
            m_vertices[3].position = { box.right(), box.bottom() };
            m_vertices[4].position = { box.left, box.bottom() };
            m_vertices[5] = m_vertices[1];

            m_index = 6;
        }

        constexpr void addShape(const Rectf32& box, const size_type nPoints)
        {
            if (nPoints) {
                const u32 nVertex(nPoints + 2);

                const vector2df size{ box.size() };
                const vector2df radius{ size / 2.0f };

                m_vertices.resize(nVertex); // + 2 for center and repeated first point
                const f64 baseAngle((2 * GeometryGenerator::PiConstant<f64>) / static_cast<f64>(nPoints));
                const auto leftTop(box.leftTop());
                for (u32 i{ 0 }; i < nPoints; ++i) {
                    const f64 angle{ (i*baseAngle) - (GeometryGenerator::PiD2Constant<f64>) };
                    const vector2dd r{ std::cos(angle) * radius.x, std::sin(angle) * radius.y };
                    m_vertices[i + 1].position = { static_cast<f32>(radius.x + r.x), static_cast<f32>(radius.y + r.y) };
                    m_vertices[i + 1].position += leftTop;
                }

                m_vertices[nPoints + 1].position = m_vertices[1].position;
                m_vertices[0].position = (box.size() / 2) + leftTop;
            }
        }

        //TO DO: Just experiment to maintain compatibility
        constexpr void addQuad(const Rectf32& box, const Rectf32 textureUV)
        {
            m_vertices.emplace_back(vector2df{ box.left, box.top }, vector2df{ textureUV.left, textureUV.top });
            m_vertices.emplace_back(vector2df{ box.right(), box.top }, vector2df{ textureUV.right(), textureUV.top });
            m_vertices.emplace_back(vector2df{ box.left,  box.bottom() }, vector2df{ textureUV.left, textureUV.bottom() });
            m_vertices.emplace_back(vector2df{ box.left,  box.bottom() }, vector2df{ textureUV.left, textureUV.bottom() });
            m_vertices.emplace_back(vector2df{ box.right(), box.top }, vector2df{ textureUV.right(), textureUV.top });
            m_vertices.emplace_back(vector2df{ box.right(), box.bottom() }, vector2df{ textureUV.right(), textureUV.bottom() });
        }

    private:
        size_type m_index{ 0U };
        vector<Vertex> &m_vertices;
    };
}

#endif
