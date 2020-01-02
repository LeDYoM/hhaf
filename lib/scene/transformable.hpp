#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#pragma once

#include "transformation.hpp"
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>

namespace lib::scene
{
class Transformable
{
public:
    Transformable() noexcept;
    virtual ~Transformable();

    PropertyState<vector2df> origin;
    PropertyState<f32> rotation;
    PropertyState<vector2df> scale;
    PropertyState<vector2df> position;

protected:
    inline bool transformationNeedsUpdate() const noexcept
    {
        return ps_hasChanged(position, origin, scale, rotation);
    }

private:
    inline void reset_needs_update() noexcept
    {
        ps_resetHasChanged(origin, rotation, scale, position);
    }

    inline const Transform &transform() const noexcept { return m_transform; }

    const Transform &updatedTransform(
        const bool local_transformation_needs_update);

public:
    void updateGlobalTransformation(
        const bool local_transformation_needs_update,
        const Transform &);
    inline const Transform &globalTransform() const noexcept { return m_globalTransform; }

    /**
        * Method to set the associated transformation to a rotation around a given point.
        * Note: this method overwrites the properties.
        *
        * @param [in] point Point to be rotated around
        * @param [in] angle Angle for the rotation
        */
    void rotateAround(const vector2df &point, const f32 angle);

    /**
        * Method to set the associated transformation to a scale around a given point.
        * Note: this method overwrites the properties.
        *
        * @param [in] point Point to be rotated around
        * @param [in] scale Scale factor
        */
    void scaleAround(const vector2df &point, const vector2df &scale);

    void rotateScaleAround(const vector2df &point, const f32 angle, const vector2df &scale);

private:
    void updateTransform() noexcept;

    Transform m_transform;
    Transform m_globalTransform;
};
} // namespace lib::scene

#endif
