#pragma once

#ifndef LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP__
#define LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP__

#include "parentrendercomponent.hpp"
#include "inputcomponent.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/scenenodetypes.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>

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
        using BaseClass_ = InputComponent;
	}
    class TextEditorComponent : public BaseClass_
	{
    private:
        using BaseClass = BaseClass_;
	public:
        virtual void onAttached() override;

		emitter<const str&> Accepted;
		emitter<> Rejected;
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
