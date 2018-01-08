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

		void onAttached() override;

		emitter<> Up;
		emitter<> Down;
		emitter<> Left;
		emitter<> Right;
		emitter<> Selected;

	private:
		ireceiver m_receiver;
	};
}

#endif
