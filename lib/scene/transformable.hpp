#pragma once

#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#include "transform.hpp"
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

    bool updateTransformIfNecessary()
    {
        if (transformationNeedsUpdate())
        {
            updateTransform();
            reset_needs_update();
            return true;
        }
        return false;
    }

    inline const Transform &globalTransform() const noexcept { return m_globalTransform; }

    /// Method to set the associated transformation to a rotation around a given point.
    /// Note: this method overwrites the properties.
    /// @param [in] point Point to be rotated around
    /// @param [in] angle Angle for the rotation
    void rotateAround(vector2df point, f32 angle);

    /// Method to set the associated transformation to a scale around a given point.
    /// Note: this method overwrites the properties.
    /// @param [in] point Point to be rotated around
    /// @param [in] scale Scale factor
    void scaleAround(vector2df point, vector2df scale);

    void rotateScaleAround(vector2df point, f32 angle, vector2df scale);

protected:
    inline bool transformationNeedsUpdate() const noexcept
    {
        return ps_hasChanged(position, origin, scale, rotation);
    }

    void updateGlobalTransformation(const Transform &);

private:
    inline void reset_needs_update() noexcept
    {
        ps_resetHasChanged(origin, rotation, scale, position);
    }

    inline const Transform &transform() const noexcept { return m_transform; }

private:
    void updateTransform() noexcept;

    Transform m_transform;
    Transform m_globalTransform;
};
} // namespace lib::scene

#endif
