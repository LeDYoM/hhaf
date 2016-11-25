#include "renderizable.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string &name, sf::PrimitiveType type, std::size_t vertexCount)
			: HasName{ name }, m_vertices{ type, vertexCount }, m_bounds{}
		{
			LOG_CONSTRUCT("Name: " << name << " of type");
		}

		u32 Renderizable::draw( sf::RenderStates &)
		{
			if (isVisible())
			{
//					window->draw()
//					window->draw(*getAsDrawable(),states);
				return 1;
			}
			return 0;
		}

		Renderizable::~Renderizable() = default;

		Rectf32 Renderizable::getLocalBounds() const
		{
			return m_bounds;
		}

		Rectf32 Renderizable::getGlobalBounds() const
		{
			return getTransform().transformRect(getLocalBounds());
		}

	}
}
