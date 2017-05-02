#include "renderwindow.hpp"
#include <lib/core/host.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/include/key.hpp>
#include <SFML/Window.hpp>
#include <lib/draw/transformation.hpp>

namespace lib
{
	namespace backend
	{
		template <typename T>
		constexpr const sf::Rect<T> fromRect(const Rect<T> &rect) { return sf::Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

		template <typename T>
		constexpr const Rect<T> toRect(const sf::Rect<T> &rect) { return Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

		template <typename T>
		constexpr const sf::Vector2<T> fromVector2d(const vector2d<T> &v) { return sf::Vector2<T>{v.x, v.y}; }

		template <typename T>
		constexpr const vector2d<T> toVector2d(const sf::Vector2<T> &v) { return vector2d<T>{v.x, v.y}; }

		input::Key doCast(const sf::Keyboard::Key &k)
		{
			int temp = k;
			return static_cast<input::Key>(temp);
		}

		sf::String getAsString(const str &other)
		{
			std::wstring wsTmp(other.begin(), other.end());
			sf::String temp(wsTmp);
			return temp;
		}

		sf::String getAsString(const char *const other)
		{
			std::string temp(other);
			return getAsString(temp);
		}

		sf::Transform asTransform(const draw::Transform &transform)
		{
			const f32 *const matrix{ transform.getMatrix() };
			return sf::Transform{ matrix[0], matrix[4], matrix[12],
				matrix[1], matrix[5], matrix[13],
				matrix[3], matrix[7], matrix[15] };

		}

		sf::RenderStates asRenderStates(const draw::RenderStates &renderStates) {
			return sf::RenderStates(sf::RenderStates::Default.blendMode,
				asTransform(renderStates.m_transform),
				renderStates.m_texture ? &(renderStates.m_texture->backEndTexture()) : nullptr,
				nullptr);
		}
	}
}
