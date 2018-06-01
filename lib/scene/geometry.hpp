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
    private:
        size_type m_index{ 0U };
        vector<Vertex> &m_vertices;
    };
}

#endif
