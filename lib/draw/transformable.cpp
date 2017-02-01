#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() noexcept :
			origin{ {},[this]() {updateTransform(); } },
			rotation{ {},[this]() {
				auto temp_rotation = static_cast<f32>(fmod(rotation(), 360));
				if (temp_rotation < 0) {
					rotation.set(temp_rotation);
				}

				updateTransform();

			} },
			position{ {} ,[this]() {updateTransform(); } },
			scale{{ 1, 1 },[this]() {updateTransform(); } },
			m_transform{} { }

		Transformable::~Transformable() = default;

		const Transform& Transformable::getTransform() const noexcept
		{
			return m_transform;
		}

		void Transformable::updateTransform()
		{
			// Recompute the combined transform
			const f32 angle = -rotation() * 3.141592654f / 180.f;
			const f32 cosine = static_cast<f32>(std::cos(angle));
			const f32 sine = static_cast<f32>(std::sin(angle));
			const f32 sxc = scale().x * cosine;
			const f32 syc = scale().y * cosine;
			const f32 sxs = scale().x * sine;
			const f32 sys = scale().y * sine;

			m_transform = Transform(sxc, sys, -origin().x * sxc - origin().y * sys + position().x,
				-sxs, syc, origin().x * sxs - origin().y * syc + position().y,
				0.f, 0.f, 1.f);
		}
	}
}
