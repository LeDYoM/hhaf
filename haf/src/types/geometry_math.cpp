#include <haf/include/core/geometry_math.hpp>
#include <cmath>

using namespace haf::core;

namespace haf::math
{
f32 length(vector4df const& v)
{
    return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

f32 length(vector3df const& v)
{
    return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

f32 length(vector2df const& v)
{
    return std::sqrt((v.x * v.x) + (v.y * v.y));
}

vector4df normalize(vector4df const& v)
{
    return v / length(v);
}

vector3df normalize(vector3df const& v)
{
    return v / length(v);
}

vector2df normalize(vector2df const& v)
{
    return v / length(v);
}

vector4df cross(vector4df const& a, vector4df const& b)
{
    return vector4df{cross(vector3df{a.x, a.y, a.z}, vector3df{b.x, b.y, b.z})};
}

vector3df cross(vector3df const& a, vector3df const& b)
{
    return vector3df{(a.y * b.z) - (b.y * a.z), (a.z * b.x) - (b.z * a.x),
                     (a.x * b.y) - (b.x * a.y)};
}

vector2df cross(vector2df const& a, vector2df const& b)
{
    auto const temp{cross(vector3df{a}, vector3df{b})};
    return vector2df{temp.x, temp.y};
}

f32 dot(vector4df const& a, vector4df const& b)
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

f32 dot(vector3df const& a, vector3df const& b)
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

f32 dot(vector2df const& a, vector2df const& b)
{
    return ((a.x * b.x) + (a.y * b.y));
}

}  // namespace haf::math