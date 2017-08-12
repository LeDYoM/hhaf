#include "transformable.hpp"
#include <cmath>


namespace lib
{
	namespace scene
	{
		namespace
		{
			inline callback_t updateTransformCallback(Transformable *t) noexcept
			{
				return lambdaToMethod<Transformable, &Transformable::updateTransform>(*t);
			}
		}
		Transformable::Transformable() noexcept : m_needsUpdate{ true },
			origin{ {}, updateTransformCallback(this) },
			rotation{ {},[this]() {
				auto temp_rotation = static_cast<f32>(fmod(rotation(), 360));
				if (temp_rotation < 0) {
					rotation.set(temp_rotation);
				}

				updateTransform();

			} },
			position{ {} , updateTransformCallback(this) },
				scale{ { 1, 1 }, updateTransformCallback(this) },
				m_transform{} {}

		Transformable::~Transformable() = default;

		void Transformable::rotateAround(const vector2df & point, const f32 angle)
		{
			origin = point;
			position = point;
			rotation = angle;
		}

		void Transformable::scaleAround(const vector2df & point, const vector2df & scale_)
		{
			origin = point;
			position = point;
			scale = scale_;
		}

		void Transformable::updateTransform() noexcept
		{
			// Recompute the combined transform
			const f32 angle{ -rotation() * 3.141592654f / 180.f };
			const f32 cosine{ static_cast<f32>(std::cos(angle)) };
			const f32 sine{ static_cast<f32>(std::sin(angle)) };
			const vector2df sc{ scale() * cosine };
			const vector2df ss{ scale() * sine };
			const vector2df orig{ origin() };
			const vector2df pos{ position() };

			m_transform = {
				sc.x,		ss.y,	(-orig.x * sc.x) - (orig.y * ss.y) + pos.x,
				-ss.x,		sc.y,	( orig.x * ss.y) - (orig.y * sc.y) + pos.y,
				0.f,		0.f,	1.f 
			};
		}
	}
}
