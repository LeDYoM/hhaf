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

		RenderStates RenderStatesStack::top() const
		{
			return m_renderStates;
		}

		void RenderStatesStack::newFrame() noexcept
		{
			m_renderStates = RenderStates();
		}

		RenderStatesStackHandle RenderStatesStack::pushChanges(const Transform *transform, const Texture *texture)
		{
			m_statesStack.emplace(std::move(m_renderStates));
			m_renderStates = RenderStates(transform ? m_renderStates.m_transform*(*transform) : m_renderStates.m_transform,
				texture );
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
