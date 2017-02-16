#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#pragma once

#include "transformation.hpp"
#include <lib/include/vector2d.hpp>
#include <lib/include/properties.hpp>
#include <lib/include/lockable.hpp>

namespace lib
{
	namespace draw
	{
		class Transformable : public Lockable
		{
		public:
			Transformable() noexcept;
			virtual ~Transformable();
			inline const Transform& transform() const noexcept { return m_transform; }
			void updateTransform() noexcept;

			Property<vector2df> origin;
			Property<f32> rotation;
			Property<vector2df> scale;
			Property<vector2df> position;

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
			void unlocked() noexcept override;
		protected:
		private:
			Transform m_transform;
			
		};
	}
}

#endif
