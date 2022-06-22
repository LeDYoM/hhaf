#include "renderizable_internal_functions.hpp"
#include "geometry_math.hpp"
#include "render_data_conversion.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::render
{
void setColor(htps::vector<backend::iColor>& colors, scene::Color const& color)
{
    backend::iColor i_color { to_backend(color) };
    for (auto&& vertex_color : colors)
    {
        vertex_color = i_color;
    }
}

void setTextureRect(vector<backend::iPosition> const& positions,
                    vector<backend::iTextureCoordinates>& texture_coordinates,
                    Rectf32 const& texture_rect)
{
    vector2df const position{texture_rect.leftTop()};
    vector2df const size{texture_rect.size()};

    LogAsserter::log_assert(
        positions.size() == texture_coordinates.size(),
        "Positions size and texture_coordinates size must match");

    for (size_type i{0U}; i < texture_coordinates.size(); ++i)
    {
        texture_coordinates[i] =
            position + ((positions[i] + vector2df{0.5F, 0.5F}) * size);
    }
}

constexpr SceneCoordinates defaultLeftBottomPosition{-0.5F, 0.5F};
constexpr SceneCoordinates defaultRightBottomPosition{0.5F, 0.5F};
constexpr SceneCoordinates defaultLeftTopPosition{-0.5F, -0.5F};
constexpr SceneCoordinates defaultRightTopPosition{0.5F, -0.5F};

void setQuad(htps::vector<backend::iPosition>& positions)
{
    using namespace scene;
    static SceneCoordinates const quad_vertex_buffer[] = {
        SceneCoordinates{defaultLeftBottomPosition},
        SceneCoordinates{defaultRightBottomPosition},
        SceneCoordinates{defaultLeftTopPosition},
        SceneCoordinates{defaultLeftTopPosition},
        SceneCoordinates{defaultRightBottomPosition},
        SceneCoordinates{defaultRightTopPosition}};

    constexpr fast_u32 kNumSizes{3U * 2U};  // 3 vertex * 2 triangles
    for (fast_u32 index{0U}; index < kNumSizes; ++index)
    {
        positions[index] = quad_vertex_buffer[index];
    }
}

void setPolygon(htps::vector<backend::iPosition>& positions)
{
    constexpr SceneCoordinates const center{0.0F, 0.0F};

    fast_u32 const kNumSides{static_cast<fast_u32>(positions.size() / 3U)};
    auto const baseAngle{PiM2Constant<f64> / static_cast<f64>(kNumSides)};
    vector2dd const radius{0.5F, 0.5F};

    f64 angle{0.0};
    fast_u32 current_index{0U};

    for (fast_u32 index{0U}; index < kNumSides; ++index)
    {
        positions[current_index++] = center;

        {
            vector2dd current_position{std::cos(angle) * radius.x,
                                       std::sin(angle) * radius.y};
            positions[current_index++] =
                static_cast<vector2df>(current_position);
        }

        angle += baseAngle;

        {
            vector2dd current_position{std::cos(angle) * radius.x,
                                       std::sin(angle) * radius.y};
            positions[current_index++] =
                static_cast<vector2df>(current_position);
        }
    }
}

}  // namespace haf::render
