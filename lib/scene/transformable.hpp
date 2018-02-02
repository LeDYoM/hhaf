#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#pragma once

#include "transformation.hpp"
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>

namespace lib
{
    namespace scene
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

            inline const Transform &transform() const noexcept { return m_transform; }
            inline const Transform &updatedTransform() { updateTransform(); return m_transform; }

            void updateGlobalTransformation(const Transform&);
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

		protected:
            inline bool transformationNeedsUpdate() noexcept {
                return position.readReset_hasChanged() || origin.readReset_hasChanged() ||
					scale.readReset_hasChanged() || rotation.readReset_hasChanged();
            }

        private:
            void updateTransform() noexcept;

            Transform m_transform;
            Transform m_globalTransform;
        };
    }
}

#endif
