#include "transformable.hpp"
#include <cmath>

namespace lib::scene
{
    Transformable::Transformable() noexcept :
        origin{ }, rotation{ }, scale{ { 1U, 1U } },
        position{ }, m_transform{ }, m_globalTransform{ }
    {}

    Transformable::~Transformable() = default;

    void Transformable::updateGlobalTransformation(const Transform &currentGlobalTransformation)
    {
        m_globalTransform = currentGlobalTransformation * updatedTransform();
    }

    void Transformable::rotateAround(const vector2df & point, const f32 angle)
    {
        origin = position = point;
        rotation = angle;
    }

    void Transformable::scaleAround(const vector2df & point, const vector2df & scale_)
    {
        origin = position = point;
        scale = scale_;
    }

    void Transformable::rotateScaleAround(const vector2df & point, const f32 angle, const vector2df & scale_)
    {
        origin = position = point;
        rotation = angle;
        scale = scale_;
    }

    void Transformable::updateTransform() noexcept
    {
        if (!transformationNeedsUpdate())
            return;

        // Recompute the combined transform
        const f32 angle{ -rotation() * 3.141592654f / 180.f };
        const f32 cosine{ static_cast<f32>(std::cos(angle)) };
        const f32 sine{ static_cast<f32>(std::sin(angle)) };
        const vector2df sc{ scale() * cosine };
        const vector2df ss{ scale() * sine };
        const vector2df orig{ origin() };
        const vector2df pos{ position() };

        m_transform = {
            sc.x,   ss.y,   (-orig.x * sc.x) - (orig.y * ss.y) + pos.x,
            -ss.x,  sc.y,   ( orig.x * ss.y) - (orig.y * sc.y) + pos.y,
            0.f,    0.f,    1.f 
        };
    }
}
