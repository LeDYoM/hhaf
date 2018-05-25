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

        constexpr GeometryGenerator(vector<Vertex> &vertexArray,
            vector_type center, vector_type radius) noexcept
            : m_vertexArray{ vertexArray }, m_center{ std::move(center) },
            m_radius{ std::move(radius) } {}

        constexpr void resetIndex() noexcept { m_index = 0U; }

        constexpr void addTriangle(const vector_type v0, 
            const vector_type v1, 
            const vector_type v2)
        {
            m_vertexArray[m_index++].position = std::move(v0);
            m_vertexArray[m_index++].position = std::move(v1);
            m_vertexArray[m_index++].position = std::move(v2);
        }

        constexpr void addTriangleFromCenter(const vector_type v0,
            const vector_type v1)
        {
            addTriangle(m_center, std::move(v0), std::move(v1));
        }

        constexpr void addTriangleFromCenterAndLast(const vector_type v0)
        {
            assert_debug(m_index > 0U, "There is no vertex in buffer");
            addTriangle(m_center, m_vertexArray[m_index-1].position, std::move(v0));
        }

    private:
        size_type m_index{ 0U };
        vector<Vertex> &m_vertexArray;
        vector_type m_center;
        vector_type m_radius;
    };
}

#endif
