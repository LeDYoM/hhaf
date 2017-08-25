#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#pragma once

#include "transformation.hpp"
#include <mtypes/include/vector2d.hpp>
#include <lib/include/properties.hpp>

namespace lib
{
	namespace scene
	{
		class Transformable
		{
		public:
			Transformable() noexcept;
			virtual ~Transformable();

			Property<vector2df> origin;
			Property<f32> rotation;
			Property<vector2df> scale;
			Property<vector2df> position;

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

			void setNeedsUpdate() noexcept { m_needsUpdate = true; }
			inline bool transformationNeedsUpdate() const noexcept { return m_needsUpdate; }
		private:
			void updateTransform() noexcept;

			bool m_needsUpdate;
			Transform m_transform;
			Transform m_globalTransform;
		};
	}
}

#endif
