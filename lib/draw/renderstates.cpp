#include "renderstates.hpp"
#include "transformation.hpp"
#include "texture.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		RenderStates::RenderStates() = default;
		RenderStates::~RenderStates() = default;

		void RenderStates::newFrame() noexcept
		{
			m_renderStates = sf::RenderStates::Default;
		}

		sf::RenderStates RenderStates::prepareNewElement(const Transform *transform, const Texture *texture)
		{
			return sf::RenderStates(m_renderStates.blendMode, 
				transform ? m_renderStates.transform*(*transform):m_renderStates.transform,
				texture,
				m_renderStates.shader);
		}
		RenderStatesStackHandle RenderStates::pushChanges(const Transform *transform, const Texture *texture)
		{
			m_statesStack.emplace(std::move(m_renderStates));
			m_renderStates = prepareNewElement(transform, texture);
			return RenderStatesStackHandle(*this);
		}
		void RenderStates::popChanges()
		{
			__ASSERT(!m_statesStack.empty(), "RenderStates stack is empty");
			m_renderStates = m_statesStack.top();
			m_statesStack.pop();
		}

		RenderStatesStackHandle::~RenderStatesStackHandle()
		{
			m_stack.popChanges();
		}

		constexpr RenderStatesStackHandle::RenderStatesStackHandle(RenderStates & stack)
			: m_stack{ stack } {}
	}
}
