#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/render/vertex_formats.hpp>

using namespace haf;
using namespace haf::core;
using namespace haf::render;

TEST_CASE("VertexFormats_for_vector_of_float", "[render][vertex_formats]")
{
    {
        using inner_type = vector4df;
        span<inner_type> data;
        CHECK(structSize<decltype(data)::value_type>() ==
              inner_type::kNumElements * sizeof(f32));
    }

    {
        using inner_type = vector3df;
        span<inner_type> data;
        CHECK(structSize<decltype(data)::value_type>() ==
              inner_type::kNumElements * sizeof(f32));
    }

    {
        using inner_type = vector2df;
        span<inner_type> data;
        CHECK(structSize<decltype(data)::value_type>() ==
              inner_type::kNumElements * sizeof(f32));
    }

    {
        using inner_type = f32;
        core::span<inner_type> data;
        CHECK(structSize<decltype(data)::value_type>() == sizeof(f32));
    }
}

TEST_CASE("VertexFormats_for_spans_of_vector_of_float",
          "[render][vertex_formats]")
{
    {
        using inner_type = vector4df;
        span<inner_type> data;
        CHECK(structSize<decltype(data)>() ==
              inner_type::kNumElements * sizeof(f32));
        CHECK(getkNumElements<inner_type>() == 4U);
    }

    {
        using inner_type = vector3df;
        span<inner_type> data;
        CHECK(structSize<decltype(data)>() ==
              inner_type::kNumElements * sizeof(f32));
        CHECK(getkNumElements<inner_type>() == 3U);
    }

    {
        using inner_type = vector2df;
        span<inner_type> data;
        CHECK(structSize<decltype(data)>() ==
              inner_type::kNumElements * sizeof(f32));
        CHECK(getkNumElements<inner_type>() == 2U);
    }

    {
        using inner_type = f32;
        core::span<inner_type> data;
        CHECK(structSize<decltype(data)>() == sizeof(f32));
        CHECK(getkNumElements<inner_type>() == 1U);
    }
}

TEST_CASE("VertexFormats_vertex_format", "[render][vertex_formats]")
{
    {
        using inner_type = Position3fNormal3fTextureCoordinates2f;
        span<inner_type> data;
        CHECK(structSize<decltype(data)>() ==
              inner_type::kNumElements * sizeof(f32));
        CHECK(getkNumElements<inner_type>() == 8U);
    }
}

TEST_CASE(
    "VertexFormats_get_vertex_format_Position3fNormal3fTextureCoordinates2f",
    "[render][vertex_formats]")
{
    using inner_type = Position3fNormal3fTextureCoordinates2f;
    VertexFormat const expected_positionvf{VertexFormat{
        BufferType::Float, 3U, 1U, offsetof(inner_type, position)}};
    VertexFormat const expected_normalvf{
        VertexFormat{BufferType::Float, 3U, 1U, offsetof(inner_type, normal)}};
    VertexFormat const expected_textureuvvf{VertexFormat{
        BufferType::Float, 2U, 1U, offsetof(inner_type, textureuv)}};

    CHECK(getVertexFormats<inner_type>().size() == 3U);
    auto const positionvf{getVertexFormats<inner_type>()[0U]};
    CHECK(positionvf.bufferType == expected_positionvf.bufferType);
    CHECK(positionvf.numElements == expected_positionvf.numElements);
    CHECK(positionvf.arraySize == expected_positionvf.arraySize);
    CHECK(positionvf.offset == expected_positionvf.offset);
    CHECK(getVertexFormats<inner_type>()[0U] == expected_positionvf);

    auto const normalvf{getVertexFormats<inner_type>()[1U]};
    CHECK(normalvf.bufferType == expected_normalvf.bufferType);
    CHECK(normalvf.numElements == expected_normalvf.numElements);
    CHECK(normalvf.arraySize == expected_normalvf.arraySize);
    CHECK(normalvf.offset == expected_normalvf.offset);
    CHECK(getVertexFormats<inner_type>()[1U] == expected_normalvf);

    auto const texturevf{getVertexFormats<inner_type>()[2U]};
    CHECK(texturevf.bufferType == expected_textureuvvf.bufferType);
    CHECK(texturevf.numElements == expected_textureuvvf.numElements);
    CHECK(texturevf.arraySize == expected_textureuvvf.arraySize);
    CHECK(texturevf.offset == expected_textureuvvf.offset);
    CHECK(getVertexFormats<inner_type>()[2U] == expected_textureuvvf);

    CHECK(getVertexFormats<inner_type>() ==
          core::array<VertexFormat, 3U>{expected_positionvf, expected_normalvf,
                                        expected_textureuvvf});
}

TEST_CASE("VertexFormats_get_vertex_format_camera_data",
          "[render][vertex_formats]")
{
    using inner_type = CameraData;
    auto const vf{getVertexFormatWithoutOffset<inner_type>()};
    CHECK(vf.arraySize == 1U);
    CHECK(vf.bufferType == BufferType::Float);
    CHECK(vf.numElements == 16U);
}
