#pragma once

#ifndef LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP
#define LIB_COMPONENT_TEXTEDITOR_INCLUDE_HPP

#include <lib/input/include/inputcomponent.hpp>
#include <mtypes/include/types.hpp>
#include <lib/scene_nodes/include/scenenodetext.hpp>

namespace lib::scene
{
class TextValidator
{
public:
    virtual bool canAddChar(const str &, const char) { return true; }
    virtual bool isValidText(const str &) { return true; }
};

class TextEditorComponent : public input::InputComponent
{
private:
    using BaseClass = InputComponent;

public:
    virtual void onAttached() override;

    emitter<const str &> Accepted;
    emitter<> Rejected;

    bool enabled{true};

    inline void setTextValidator(uptr<TextValidator> nTextValidator) noexcept
    {
        std::swap(m_textValidator, nTextValidator);
    }

private:
    ireceiver m_receiver;
    uptr<TextValidator> m_textValidator;
    str m_originalText;
};
} // namespace lib::scene

#endif
