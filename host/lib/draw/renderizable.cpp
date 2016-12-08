#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string &name, PrimitiveType type, std::size_t vertexCount)
			: HasName{ name }, m_vertices{ type, vertexCount }, m_bounds{}, m_texture{ nullptr }
		{
			logConstruct("Name: ", name );
		}

		Renderizable::~Renderizable() = default;

		void Renderizable::draw()
		{
			auto handle = host().rStates().pushChanges(&getTransform(), m_texture.get());
			m_vertices.draw();
		}
	}
}
