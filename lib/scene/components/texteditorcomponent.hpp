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
	class TextValidator
	{
	public:
		virtual bool canAddChar(const str&, const char) = 0;
		virtual bool isValidText(const str&) = 0;
	};
	namespace
	{
		using BaseClass_ = RenderizableSceneNodeComponent<nodes::NodeText, InputComponent>;
	}
	class TextEditorComponent : public BaseClass_
	{
	public:
		using BaseClass = BaseClass_;

		virtual void onAttached() override;

		emitter<const str&> accepted;
		emitter<> rejected;
		inline void setTextValidator(sptr<TextValidator> nTextValidator) {
			m_textValidator = std::move(nTextValidator);
		}
	private:
		ireceiver m_receiver;
		sptr<TextValidator> m_textValidator;
		str m_originalText;
	};
}

#endif
