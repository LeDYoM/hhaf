#pragma once

#ifndef LIB_COMPONENT_PARENT_RENDER_INCLUDE_HPP__
#define LIB_COMPONENT_PARENT_RENDER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib::scene
{
	template <typename RenderizableT>
	class ParentRenderComponent : public IComponent
	{
	public:
		ParentRenderComponent() {}
		virtual ~ParentRenderComponent() {}

		void onAttached() override {
			m_node = getRenderNodeToAttach();
		}
<<<<<<< HEAD
=======
<<<<<<< HEAD

=======
<<<<<<< HEAD
       
=======

        template <typename T>
        using IComponent::attachedNodeAs();
        
>>>>>>> development_1.4_linux_compile_and_scripting
>>>>>>> 4f8c61645b145159198cccb23cd63049da16ac7f
>>>>>>> development_1.4_linux_compile_and_scripting
		sptr<RenderizableT> node() noexcept { return m_node; }
		const sptr<RenderizableT> node() const noexcept { return m_node; }

	private:
		virtual sptr<RenderizableT> getRenderNodeToAttach() = 0;
		sptr<RenderizableT> m_node;
	};
}

#endif
