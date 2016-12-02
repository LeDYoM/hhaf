#include "renderizable.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string &name, sf::PrimitiveType type, std::size_t vertexCount)
			: HasName{ name }, m_vertices{ static_cast<PrimitiveType>(type), vertexCount }, m_bounds{}
		{
			logConstruct("Name: ", name );
		}

		void Renderizable::draw(sf::RenderStates &)
		{
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
