#include "renderwindow.hpp"
#include <lib/core/host.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/include/key.hpp>
#include <lib/scene/transformation.hpp>

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

			inline sf::String getAsString(const str &other)
			{
				std::wstring wsTmp(other.begin(), other.end());
				sf::String temp(wsTmp);
				return temp;
			}

			inline sf::String getAsString(const char *const other)
			{
				const str temp(other);
				return getAsString(temp);
			}

			inline sf::Transform asTransform(const scene::Transform &transform)
			{
				const f32 *const matrix{ transform.getMatrix() };
				return sf::Transform{ matrix[0], matrix[4], matrix[12],
					matrix[1], matrix[5], matrix[13],
					matrix[3], matrix[7], matrix[15] };

			}

			inline const sf::Texture *const asTexture(const scene::Texture*texture)
			{
				if (texture) {
					ITexture*t = texture->backEndTexture().get();
					if (t) {
						if (auto tmp = dynamic_cast<Texture*>(t)) {
							return &(tmp->backEndTexture());
						}
						if (auto tmp = dynamic_cast<TextureTTFont*>(t)) {
							return &(tmp->backEndTexture());
						}
					}
				}
				return nullptr;
			}

			inline const sf::RenderStates asRenderStates(const scene::RenderStates &renderStates)
			{
				return sf::RenderStates(sf::RenderStates::Default.blendMode,
					asTransform(renderStates.m_transform),
					asTexture(renderStates.m_texture),
					nullptr);
			}
		}
	}
}
