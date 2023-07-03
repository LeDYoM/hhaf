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
void addPositionsFace(vvector3d<T>& v, FaceDirection const fDirection)
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
void addPositionsCube(vvector3d<T>& v)
{
    addPositionsFace(v, FaceDirection::Down);
    addPositionsFace(v, FaceDirection::Right);
    addPositionsFace(v, FaceDirection::Up);
    addPositionsFace(v, FaceDirection::Left);
    addPositionsFace(v, FaceDirection::Back);
    addPositionsFace(v, FaceDirection::Front);
}

}  // namespace fmath

#endif
