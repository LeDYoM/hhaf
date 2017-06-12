#ifndef LIB_DRAW_RENDERSTATESSTACK_INCLUDE_HPP__
#define LIB_DRAW_RENDERSTATESSTACK_INCLUDE_HPP__

#pragma  once

#include "texture.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/renderstates.hpp>

#include <stack>

namespace lib
{
	namespace scene
	{
		class Transform;
		class Texture;
		class RenderStatesStack;
		class RenderStatesStackHandle final
		{
		public:
			~RenderStatesStackHandle();
		private:
			constexpr RenderStatesStackHandle(RenderStatesStack &stack);
			RenderStatesStack &m_stack;
			friend class RenderStatesStack;
		};

		class RenderStatesStack final
		{
		public:
			RenderStatesStack();
			~RenderStatesStack();

			const RenderStates &top() const noexcept;
			void newFrame() noexcept;
			RenderStatesStackHandle pushChanges(const Transform *transform, const Texture *texture);
			void popChanges();
		private:
			RenderStates m_renderStates;
			std::stack<RenderStates> m_statesStack;
			friend class RenderStatesStackHandle;
		};
	}
}

#endif
