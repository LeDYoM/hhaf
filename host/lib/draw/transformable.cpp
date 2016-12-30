#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() noexcept :
			origin{ {},[this](const auto&) {updateTransform(); } },
			rotation{ {},[this](const auto&angle) {
				auto temp_rotation = static_cast<f32>(fmod(angle, 360));
				if (temp_rotation < 0) {
					while (temp_rotation<0) temp_rotation += 360.f;
					rotation.set(temp_rotation);
				}

				if (temp_rotation > 360.f) {
					while (temp_rotation > 360.f) temp_rotation -= 360.f;
					rotation.set(temp_rotation);
				}

				updateTransform();

			} },
			m_position{ 0, 0 },
			m_scale{ 1, 1 },
			m_transform{} { }

		Transformable::~Transformable() = default;

		void Transformable::setPosition(const vector2df& position)
		{
			m_position = position;
			updateTransform();
		}

		void Transformable::setScale(const vector2df& factors)
		{
			m_scale = factors;
			updateTransform();
		}

		const vector2df& Transformable::getPosition() const
		{
			return m_position;
		}

		const vector2df& Transformable::getScale() const
		{
			return m_scale;
		}

		const Transform& Transformable::getTransform() const noexcept
		{
			return m_transform;
		}

		void Transformable::updateTransform()
		{
			// Recompute the combined transform
			const f32 angle = -rotation.get() * 3.141592654f / 180.f;
			const f32 cosine = static_cast<f32>(std::cos(angle));
			const f32 sine = static_cast<f32>(std::sin(angle));
			const f32 sxc = m_scale.x * cosine;
			const f32 syc = m_scale.y * cosine;
			const f32 sxs = m_scale.x * sine;
			const f32 sys = m_scale.y * sine;
			const f32 tx = -origin.get().x * sxc - origin.get().y * sys + m_position.x;
			const f32 ty = origin.get().x * sxs - origin.get().y * syc + m_position.y;

			m_transform = Transform(sxc, sys, tx,
				-sxs, syc, ty,
				0.f, 0.f, 1.f);
		}
	}
}
