#pragma once

#ifndef LIB_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP__
#define LIB_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "parentrendercomponent.hpp"
#include <lib/scene/scenenodetypes.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace lib::scene
{
	class DiscreteTextComponent : public RenderizableSceneNodeComponent<nodes::NodeText, IComponent>
	{
	public:
		using BaseClass = RenderizableSceneNodeComponent<nodes::NodeText, IComponent>;
		DiscreteTextComponent() {}
		virtual ~DiscreteTextComponent() {}

		virtual void onAttached() override {
			BaseClass::onAttached();
		}

		Property<bool> circleAroud{ true };
		Property<u32> index{ 0 };
		Property<string_vector> data;
		void incrementIndex() noexcept;
		void decrementIndex() noexcept;

		virtual void update() override final;
	private:
		void _setText(const str&nText);
	};
}

#endif
