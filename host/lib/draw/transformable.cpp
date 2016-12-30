#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() noexcept :
			m_origin{ 0, 0 },
			m_position{ 0, 0 },
			m_rotation{ 0 },
			m_scale{ 1, 1 },
			m_transform{} { }

		Transformable::~Transformable() = default;

		void Transformable::setPosition(const vector2df& position)
		{
			m_position = position;
			updateTransform();
		}

		void Transformable::setRotation(const f32 angle)
		{
			m_rotation = static_cast<f32>(fmod(angle, 360));
			if (m_rotation < 0)
				m_rotation += 360.f;
			updateTransform();
		}

		void Transformable::setScale(const vector2df& factors)
		{
			m_scale = factors;
			updateTransform();
		}

		void Transformable::setOrigin(const vector2df& origin)
		{
			m_origin = origin;
			updateTransform();
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

		void Transformable::move(const vector2df& offset)
		{
			setPosition(m_position + offset);
		}

		void Transformable::rotate(const f32 angle)
		{
			setRotation(m_rotation + angle);
		}

		void Transformable::scale(const vector2df& factor)
		{
			setScale(m_scale * factor);
		}

		const Transform& Transformable::getTransform() const noexcept
		{
			return m_transform;
		}

		void Transformable::updateTransform()
		{
			// Recompute the combined transform
			const f32 angle = -m_rotation * 3.141592654f / 180.f;
			const f32 cosine = static_cast<f32>(std::cos(angle));
			const f32 sine = static_cast<f32>(std::sin(angle));
			const f32 sxc = m_scale.x * cosine;
			const f32 syc = m_scale.y * cosine;
			const f32 sxs = m_scale.x * sine;
			const f32 sys = m_scale.y * sine;
			const f32 tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
			const f32 ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

			m_transform = Transform(sxc, sys, tx,
				-sxs, syc, ty,
				0.f, 0.f, 1.f);
		}
	}
}
