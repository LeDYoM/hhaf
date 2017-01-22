#ifndef LIB_DRAW_VIEW_INCLUDE_HPP__
#define LIB_DRAW_VIEW_INCLUDE_HPP__
#pragma once

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/include/rect.hpp>
#include <lib/include/properties.hpp>
#include <lib/draw/transformation.hpp>
#include <SFML/Graphics/View.hpp>

namespace lib
{
	namespace draw
	{
		class View
		{
		public:
			View();
			explicit View(const sf::View &_view);
			explicit View(Rectf32 rectangle);
			void updateTransform();
			const Transform& getTransform() const;
			const sf::View &externalView() const;

			Property<Rectf32> perspective;
			Property<f32> rotation;
			Property<Rectf32> viewport;
		private:
			Transform m_transform;
			sf::View m_cachedView;
		};
	}
}

#endif
