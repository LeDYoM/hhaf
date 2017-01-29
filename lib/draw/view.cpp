#include "view.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{

		View::View(Rectf32 rectangle) :
			perspective{ {},[this](const auto) { updateTransform(); } },
			rotation{ {}, [this](const auto) { updateTransform(); } },
			viewport{ std::move(rectangle), [this](const auto) { updateTransform(); } }
		{
			updateTransform();
		}

		View::View() : View{{0,0,1000.f,1000.f}} {}

		View::View(const sf::View &_view) : View()
		{
			m_cachedView = _view;
		}

		void View::updateTransform()
		{
			auto center(perspective().center());
			auto size(perspective().size());
			float angle = rotation() * 3.141592654f / 180.f;
			float cosine = static_cast<float>(std::cos(angle));
			float sine = static_cast<float>(std::sin(angle));
			float tx = -center.x * cosine - center.y * sine + center.x;
			float ty = center.x * sine - center.y * cosine + center.y;

			// Projection components
			float a = 2.f / size.x;
			float b = -2.f / size.y;
			float c = -a * center.x;
			float d = -b * center.y;

			// Rebuild the projection matrix
			m_transform = Transform(a * cosine, a * sine, a * tx + c,
				-b * sine, b * cosine, b * ty + d,
				0.f, 0.f, 1.f);

			m_cachedView.reset(sf::FloatRect(perspective().left, perspective().top, 
				perspective().width, perspective().height));
			m_cachedView.setRotation(rotation());
		}

		const Transform& View::getTransform() const
		{
			return m_transform;
		}

		const sf::View & View::externalView() const
		{
			return m_cachedView;
		}

	}
}
