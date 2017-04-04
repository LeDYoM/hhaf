#include "renderstatesstack.hpp"
#include "transformation.hpp"
#include "texture.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		RenderStatesStack::RenderStatesStack() = default;
		RenderStatesStack::~RenderStatesStack() = default;

		void RenderStatesStack::newFrame() noexcept
		{
			m_renderStates = sf::RenderStates::Default;
		}

		RenderStatesStackHandle RenderStatesStack::pushChanges(const Transform *transform, const Texture *texture)
		{
			m_statesStack.emplace(std::move(m_renderStates));
			m_renderStates = sf::RenderStates(m_renderStates.blendMode,
				transform ? m_renderStates.transform*(*transform) : m_renderStates.transform,
				texture ? texture->backEndTexture() : nullptr,
				m_renderStates.shader);
			return RenderStatesStackHandle(*this);
		}
		void RenderStatesStack::popChanges()
		{
			__ASSERT(!m_statesStack.empty(), "RenderStates stack is empty");
			m_renderStates = m_statesStack.top();
			m_statesStack.pop();
		}

		RenderStatesStackHandle::~RenderStatesStackHandle()
		{
			m_stack.popChanges();
		}

		constexpr RenderStatesStackHandle::RenderStatesStackHandle(RenderStatesStack & stack)
			: m_stack{ stack } {}
	}
}
