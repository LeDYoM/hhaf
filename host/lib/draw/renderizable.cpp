#include "renderizable.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string &name, PrimitiveType type, std::size_t vertexCount)
			: HasName{ name }, m_vertices{ type, vertexCount }, m_bounds{}
		{
			logConstruct("Name: ", name );
		}

		Renderizable::~Renderizable() = default;

		Rectf32 Renderizable::getLocalBounds() const
		{
			return m_bounds;
		}
	}
}
