#pragma once

#ifndef ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP__
#define ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/components/inputcomponent.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	class MenuPageInputComponent : public InputComponent
	{
	public:
		using BaseClass = InputComponent;
		using InputComponent::InputComponent;
		virtual ~MenuPageInputComponent() = default;

		void keyPressed(const input::Key&) override;
		void keyReleased(const input::Key&) override;

		emitter<> goDown;
		emitter<> goUp;
		emitter<> goLeft;
		emitter<> goRight;

		inline u32 selectedItem() const noexcept { return m_selectedItem; }

	private:
		u32 m_previouslySelectedItem;
		u32 m_selectedItem;

		ireceiver m_receiver;
	};
}

#endif
