#pragma once

#ifndef LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP
#define LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP

#include "inputcomponent.hpp"
#include <mtypes/include/types.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>

namespace lib::scene
{
    class TextValidator
    {
    public:
        virtual bool canAddChar(const str&, const char) { return true; }
        virtual bool isValidText(const str&) { return true; }
    };

    class TextEditorComponent : public InputComponent
    {
    private:
        using BaseClass = InputComponent;
    public:
        virtual void onAttached() override;

        emitter<const str&> Accepted;
        emitter<> Rejected;

        bool enabled{true};

        inline void setTextValidator(sptr<TextValidator> nTextValidator) noexcept
        {
            std::swap(m_textValidator, nTextValidator);
        }
    private:
        ireceiver m_receiver;
        sptr<TextValidator> m_textValidator;
        str m_originalText;
    };
}

#endif
