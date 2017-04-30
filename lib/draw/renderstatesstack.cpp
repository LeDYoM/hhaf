#include "renderstatesstack.hpp"
#include "transformation.hpp"
#include "texturev1.hpp"
#include <lib/core/log.hpp>
#include <lib/core/debugsystem.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		RenderStatesStack::RenderStatesStack() = default;
		RenderStatesStack::~RenderStatesStack() = default;

		const RenderStates &RenderStatesStack::top() const noexcept
		{
			return m_renderStates;
		}

		DV_ONLY(static u32 multiplications{ 0 };)

		void RenderStatesStack::newFrame() noexcept
		{
			DV_ONLY(debugSystem().setMatrixMultiplicationPerFrame(multiplications);
			multiplications = 0;)
			m_renderStates = RenderStates{};
		}

		RenderStatesStackHandle RenderStatesStack::pushChanges(const Transform *transform, const TextureV1 *texture)
		{
			DV_ONLY(if (transform) {
				++multiplications;
			})

			m_statesStack.emplace(std::move(m_renderStates));
			m_renderStates = RenderStates{ transform ? m_renderStates.m_transform*(*transform) : m_renderStates.m_transform, texture };
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

		constexpr RenderStatesStackHandle::RenderStatesStackHandle(RenderStatesStack & stack) : m_stack{ stack } {}
	}
}
