FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VVECTOR_FUNCTIONS_INCLUDE_HPP
#define FACIL_MATH_VVECTOR_FUNCTIONS_INCLUDE_HPP

#include <facil_math/include/vvector.hpp>

namespace fmath
{
namespace tps = htps;

enum class FaceDirection : tps::u32
{
    Front = 0U,
    Back,
    Left,
    Up,
    Right,
    Down
};

template <typename T>
void addPositionFace(vvector3d<T>& v, FaceDirection const fDirection)
{
    switch (fDirection)
    {
        case FaceDirection::Front:
            v.push_triangle({MinusOne<T>, MinusOne<T>, One<T>},
                            {One<T>, MinusOne<T>, One<T>},
                            {One<T>, One<T>, One<T>});
            v.push_triangle({One<T>, One<T>, One<T>},
                            {MinusOne<T>, One<T>, One<T>},
                            {MinusOne<T>, MinusOne<T>, One<T>});
            break;
        case FaceDirection::Back:
            v.push_triangle({MinusOne<T>, One<T>, MinusOne<T>},
                            {One<T>, One<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, MinusOne<T>});
            v.push_triangle({One<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, MinusOne<T>});
            break;
        case FaceDirection::Left:
            v.push_triangle({MinusOne<T>, One<T>, MinusOne<T>},
                            {MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, One<T>});
            v.push_triangle({MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, MinusOne<T>, One<T>},
                            {MinusOne<T>, One<T>, One<T>});
            break;
        case FaceDirection::Up:
            v.push_triangle({One<T>, One<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, MinusOne<T>},
                            {One<T>, One<T>, One<T>});
            v.push_triangle({MinusOne<T>, One<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, One<T>},
                            {One<T>, One<T>, One<T>});
            break;
        case FaceDirection::Right:
            v.push_triangle({One<T>, MinusOne<T>, MinusOne<T>},
                            {One<T>, One<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, One<T>});
            v.push_triangle({One<T>, One<T>, MinusOne<T>},
                            {One<T>, One<T>, One<T>},
                            {One<T>, MinusOne<T>, One<T>});
            break;
        case FaceDirection::Down:
            v.push_triangle({MinusOne<T>, MinusOne<T>, One<T>},
                            {MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, MinusOne<T>});
            v.push_triangle({One<T>, MinusOne<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, One<T>},
                            {MinusOne<T>, MinusOne<T>, One<T>});
            break;
        default:
            break;
    }
}

template <typename T>
void addTextureUVFace(vvector2d<T>& v, FaceDirection const fDirection)
{
    switch (fDirection)
    {
        case FaceDirection::Front:
            v.push_triangle({Zero<T>, Zero<T>}, {One<T>, Zero<T>},
                            {One<T>, One<T>});
            v.push_triangle({One<T>, One<T>}, {Zero<T>, One<T>},
                            {Zero<T>, Zero<T>});
            break;
        case FaceDirection::Back:
            v.push_triangle({Zero<T>, One<T>}, {One<T>, One<T>},
                            {One<T>, Zero<T>});
            v.push_triangle({One<T>, Zero<T>}, {Zero<T>, Zero<T>},
                            {Zero<T>, One<T>});
            break;
        case FaceDirection::Left:
            v.push_triangle({One<T>, Zero<T>}, {Zero<T>, Zero<T>},
                            {One<T>, One<T>});
            v.push_triangle({Zero<T>, Zero<T>}, {Zero<T>, One<T>},
                            {One<T>, One<T>});
            break;
        case FaceDirection::Up:
            v.push_triangle({One<T>, Zero<T>}, {Zero<T>, Zero<T>},
                            {One<T>, One<T>});
            v.push_triangle({Zero<T>, Zero<T>}, {Zero<T>, One<T>},
                            {One<T>, One<T>});
            break;
        case FaceDirection::Right:
            v.push_triangle({Zero<T>, Zero<T>}, {One<T>, Zero<T>},
                            {Zero<T>, One<T>});
            v.push_triangle({One<T>, Zero<T>}, {One<T>, One<T>},
                            {Zero<T>, One<T>});
            break;
        case FaceDirection::Down:
            v.push_triangle({Zero<T>, One<T>}, {Zero<T>, Zero<T>},
                            {One<T>, Zero<T>});
            v.push_triangle({One<T>, Zero<T>}, {One<T>, One<T>},
                            {Zero<T>, One<T>});
            break;
        default:
            break;
    }
}

template <typename T>
void addNormalFace(vvector3d<T>& v, FaceDirection const fDirection)
{
    switch (fDirection)
    {
        case FaceDirection::Front:
            v.push_triangle({MinusOne<T>, MinusOne<T>, One<T>},
                            {One<T>, MinusOne<T>, One<T>},
                            {One<T>, One<T>, One<T>});
            v.push_triangle({One<T>, One<T>, One<T>},
                            {MinusOne<T>, One<T>, One<T>},
                            {MinusOne<T>, MinusOne<T>, One<T>});
            break;
        case FaceDirection::Back:
            v.push_triangle({MinusOne<T>, One<T>, MinusOne<T>},
                            {One<T>, One<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, MinusOne<T>});
            v.push_triangle({One<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, MinusOne<T>});
            break;
        case FaceDirection::Left:
            v.push_triangle({MinusOne<T>, One<T>, MinusOne<T>},
                            {MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, One<T>});
            v.push_triangle({MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {MinusOne<T>, MinusOne<T>, One<T>},
                            {MinusOne<T>, One<T>, One<T>});
            break;
        case FaceDirection::Up:
            v.push_triangle({One<T>, One<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, MinusOne<T>},
                            {One<T>, One<T>, One<T>});
            v.push_triangle({MinusOne<T>, One<T>, MinusOne<T>},
                            {MinusOne<T>, One<T>, One<T>},
                            {One<T>, One<T>, One<T>});
            break;
        case FaceDirection::Right:
            v.push_triangle({One<T>, MinusOne<T>, MinusOne<T>},
                            {One<T>, One<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, One<T>});
            v.push_triangle({One<T>, One<T>, MinusOne<T>},
                            {One<T>, One<T>, One<T>},
                            {One<T>, MinusOne<T>, One<T>});
            break;
        case FaceDirection::Down:
            v.push_triangle({MinusOne<T>, MinusOne<T>, One<T>},
                            {MinusOne<T>, MinusOne<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, MinusOne<T>});
            v.push_triangle({One<T>, MinusOne<T>, MinusOne<T>},
                            {One<T>, MinusOne<T>, One<T>},
                            {MinusOne<T>, MinusOne<T>, One<T>});
            break;
        default:
            break;
    }
}

template <typename T>
void addColorFace(vvector4d<T>& v,
                  FaceDirection const fDirection,
                  const vector4df& color)
{
    switch (fDirection)
    {
        case FaceDirection::Front:
            v.push_triangle(color, color, color);
            v.push_triangle(color, color, color);
            break;
        case FaceDirection::Back:
            v.push_triangle(color, color, color);
            v.push_triangle(color, color, color);
            break;
        case FaceDirection::Left:
            v.push_triangle(color, color, color);
            v.push_triangle(color, color, color);
            break;
        case FaceDirection::Up:
            v.push_triangle(color, color, color);
            v.push_triangle(color, color, color);
            break;
        case FaceDirection::Right:
            v.push_triangle(color, color, color);
            v.push_triangle(color, color, color);
            break;
        case FaceDirection::Down:
            v.push_triangle(color, color, color);
            v.push_triangle(color, color, color);
            break;
        default:
            break;
    }
}

template <typename T>
void addPositionsCube(vvector3d<T>& v)
{
    addPositionFace(v, FaceDirection::Down);
    addPositionFace(v, FaceDirection::Right);
    addPositionFace(v, FaceDirection::Up);
    addPositionFace(v, FaceDirection::Left);
    addPositionFace(v, FaceDirection::Back);
    addPositionFace(v, FaceDirection::Front);
}

template <typename T>
void addTextureUVCube(vvector2d<T>& v)
{
    addTextureUVFace(v, FaceDirection::Down);
    addTextureUVFace(v, FaceDirection::Right);
    addTextureUVFace(v, FaceDirection::Up);
    addTextureUVFace(v, FaceDirection::Left);
    addTextureUVFace(v, FaceDirection::Back);
    addTextureUVFace(v, FaceDirection::Front);
}

template <typename T>
void addNormalCube(vvector3d<T>& v)
{
    addNormalFace(v, FaceDirection::Down);
    addNormalFace(v, FaceDirection::Right);
    addNormalFace(v, FaceDirection::Up);
    addNormalFace(v, FaceDirection::Left);
    addNormalFace(v, FaceDirection::Back);
    addNormalFace(v, FaceDirection::Front);
}

template <typename T>
void addColorCube(vvector4d<T>& v, const vector4df& color)
{
    addColorFace(v, FaceDirection::Down, color);
    addColorFace(v, FaceDirection::Right, color);
    addColorFace(v, FaceDirection::Up, color);
    addColorFace(v, FaceDirection::Left, color);
    addColorFace(v, FaceDirection::Back, color);
    addColorFace(v, FaceDirection::Front, color);
}

template <typename T>
void addColorCube(vvector4d<T>& v, const tps::array<vector4df, 6>& colors)
{
    addColorFace(v, FaceDirection::Down, colors[0]);
    addColorFace(v, FaceDirection::Right, colors[1]);
    addColorFace(v, FaceDirection::Up, colors[2]);
    addColorFace(v, FaceDirection::Left, colors[3]);
    addColorFace(v, FaceDirection::Back, colors[4]);
    addColorFace(v, FaceDirection::Front, colors[5]);
}

}  // namespace fmath

#endif
