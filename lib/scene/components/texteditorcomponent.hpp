#pragma once

#ifndef LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP__
#define LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP__

#include "parentrendercomponent.hpp"
#include "inputcomponent.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenodetypes.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace lib::scene
{
	namespace
	{
		using BaseClass_ = RenderizableSceneNodeComponent<nodes::NodeText, InputComponent>;

		class TextEditorComponent : public BaseClass_
		{
		public:
			using BaseClass = BaseClass_;
			TextEditorComponent() {}
			virtual ~TextEditorComponent() {}

			virtual void onAttached() override;

			virtual void update() override final;
		private:
			ireceiver m_receiver;

		};
	}
}

#endif
