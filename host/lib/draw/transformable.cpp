#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() :
			m_origin(0, 0),
			m_position(0, 0),
			m_rotation(0),
			m_scale(1, 1),
			m_transform{},
			m_transformNeedUpdate(true),
			m_inverseTransform{},
			m_inverseTransformNeedUpdate(true)
		{
		}

		Transformable::~Transformable()
		{
		}

		void Transformable::setPosition(const f32 x, const f32 y)
		{
			m_position.x = x;
			m_position.y = y;
			m_transformNeedUpdate = true;
			m_inverseTransformNeedUpdate = true;
		}

		void Transformable::setPosition(const vector2df& position)
		{
			setPosition(position.x, position.y);
		}

		void Transformable::setRotation(const f32 angle)
		{
			m_rotation = static_cast<f32>(fmod(angle, 360));
			if (m_rotation < 0)
				m_rotation += 360.f;

			m_transformNeedUpdate = true;
			m_inverseTransformNeedUpdate = true;
		}

		void Transformable::setScale(const f32 factorX, const f32 factorY)
		{
			m_scale.x = factorX;
			m_scale.y = factorY;
			m_transformNeedUpdate = true;
			m_inverseTransformNeedUpdate = true;
		}

		void Transformable::setScale(const vector2df& factors)
		{
			setScale(factors.x, factors.y);
		}

		void Transformable::setOrigin(const f32 x, const f32 y)
		{
			m_origin.x = x;
			m_origin.y = y;
			m_transformNeedUpdate = true;
			m_inverseTransformNeedUpdate = true;
		}

		void Transformable::setOrigin(const vector2df& origin)
		{
			setOrigin(origin.x, origin.y);
		}

		const vector2df& Transformable::getPosition() const
		{
			return m_position;
		}

		float Transformable::getRotation() const
		{
			return m_rotation;
		}

		const vector2df& Transformable::getScale() const
		{
			return m_scale;
		}

		const vector2df& Transformable::getOrigin() const
		{
			return m_origin;
		}

		void Transformable::move(const f32 offsetX, const f32 offsetY)
		{
			setPosition(m_position.x + offsetX, m_position.y + offsetY);
		}

		void Transformable::move(const vector2df& offset)
		{
			setPosition(m_position.x + offset.x, m_position.y + offset.y);
		}

		void Transformable::rotate(const f32 angle)
		{
			setRotation(m_rotation + angle);
		}

		void Transformable::scale(const f32 factorX, const f32 factorY)
		{
			setScale(m_scale.x * factorX, m_scale.y * factorY);
		}

		void Transformable::scale(const vector2df& factor)
		{
			setScale(m_scale.x * factor.x, m_scale.y * factor.y);
		}

		const sf::Transform& Transformable::getTransform() const
		{
			// Recompute the combined transform if needed
			if (m_transformNeedUpdate)
			{
				const f32 angle = -m_rotation * 3.141592654f / 180.f;
				const f32 cosine = static_cast<f32>(std::cos(angle));
				const f32 sine = static_cast<f32>(std::sin(angle));
				const f32 sxc = m_scale.x * cosine;
				const f32 syc = m_scale.y * cosine;
				const f32 sxs = m_scale.x * sine;
				const f32 sys = m_scale.y * sine;
				const f32 tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
				const f32 ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

				m_transform = sf::Transform(sxc, sys, tx,
					-sxs, syc, ty,
					0.f, 0.f, 1.f);
				m_transformNeedUpdate = false;
			}

			return m_transform;
		}

		const sf::Transform& Transformable::getInverseTransform() const
		{
			// Recompute the inverse transform if needed
			if (m_inverseTransformNeedUpdate)
			{
				m_inverseTransform = getTransform().getInverse();
				m_inverseTransformNeedUpdate = false;
			}

			return m_inverseTransform;
		}
	}
}
