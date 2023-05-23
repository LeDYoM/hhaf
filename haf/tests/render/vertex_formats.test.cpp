#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/render/vertex_formats.hpp>

using namespace haf;
using namespace haf::core;
using namespace haf::render;

TEST_CASE("VertexFormats_for_vector_of_float", "[render][vertex_formats]")
{
    CHECK(getVertexFormat<vector4df>() ==
          VertexFormat{BufferType::Float, 4U, 1U});

    CHECK(getVertexFormat<vector3df>() ==
          VertexFormat{BufferType::Float, 3U, 1U});

    CHECK(getVertexFormat<vector2df>() ==
          VertexFormat{BufferType::Float, 2U, 1U});

    CHECK(getVertexFormat<f32>() == VertexFormat{BufferType::Float, 1U, 1U});
}

TEST_CASE("VertexFormats_for_vector_of_int", "[render][vertex_formats]")
{
    CHECK(getVertexFormat<vector4ds32>() ==
          VertexFormat{BufferType::Int, 4U, 1U});

    CHECK(getVertexFormat<vector3ds32>() ==
          VertexFormat{BufferType::Int, 3U, 1U});

    CHECK(getVertexFormat<vector2ds32>() ==
          VertexFormat{BufferType::Int, 2U, 1U});

    CHECK(getVertexFormat<s32>() == VertexFormat{BufferType::Int, 1U, 1U});
}
