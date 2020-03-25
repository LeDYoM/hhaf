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
    virtual bool canAddChar(const mtps::str&, const char) { return true; }
    virtual bool isValidText(const mtps::str&) { return true; }
};

class TextEditorComponent : public input::InputComponent
{
private:
    using BaseClass = InputComponent;

public:
    virtual void onAttached() override;

    mtps::emitter<const mtps::str&> Accepted;
    mtps::emitter<> Rejected;

    bool enabled{true};

    inline void setTextValidator(mtps::uptr<TextValidator> nTextValidator) noexcept
    {
        std::swap(m_textValidator, nTextValidator);
    }

private:
    mtps::ireceiver m_receiver;
    mtps::uptr<TextValidator> m_textValidator;
    mtps::str m_originalText;
};
} // namespace lib::scene

#endif
