#include "renderwindow.hpp"
#include <lib/core/host.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/include/key.hpp>
#include <lib/scene/transformation.hpp>
#include <lib/scene/texture.hpp>
#include <lib/backend/itexture.hpp>
#include "texture.hpp"
#include "texturettfont.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			template <typename T>
			constexpr const sf::Rect<T> fromRect(const Rect<T> &rect) { return sf::Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

			template <typename T>
			constexpr const Rect<T> toRect(const sf::Rect<T> &rect) { return Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

			template <typename T>
			constexpr const sf::Vector2<T> fromVector2d(const vector2d<T> &v) { return sf::Vector2<T>{v.x, v.y}; }

			template <typename T>
			constexpr const vector2d<T> toVector2d(const sf::Vector2<T> &v) { return vector2d<T>{v.x, v.y}; }

			inline input::Key doCast(const sf::Keyboard::Key &k)
			{
				int temp = k;
				return static_cast<input::Key>(temp);
			}

			inline sf::String getAsString(const inline_str &other)
			{
				std::wstring wsTmp(other.str, other.str + other.size);
				sf::String temp(wsTmp);
				return temp;
			}

			inline sf::Transform asTransform(const f32* matrix)
			{
				return sf::Transform{ matrix[0], matrix[4], matrix[12],
					matrix[1], matrix[5], matrix[13],
					matrix[3], matrix[7], matrix[15] };

			}

			inline const sf::Texture *const asTexture(const ITexture*t)
			{
				if (t) {
					if (auto tmp = dynamic_cast<const Texture*>(t)) {
						return &(tmp->backEndTexture());
					}
					if (auto tmp = dynamic_cast<const TextureTTFont*>(t)) {
						return &(tmp->backEndTexture());
					}
				}
				return nullptr;
			}

			inline const sf::RenderStates asRenderStates(const f32 *matrix, const ITexture *texture)
			{
				return sf::RenderStates(sf::RenderStates::Default.blendMode,
					asTransform(matrix),
					asTexture(texture),
					nullptr);
			}
		}
	}
}
