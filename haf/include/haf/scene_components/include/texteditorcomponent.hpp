#ifndef HAF_COMPONENT_TEXTEDITOR_INCLUDE_HPP
#define HAF_COMPONENT_TEXTEDITOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/connection.hpp>
#include <haf/input/include/virtual_input_component.hpp>

namespace haf::scene
{
class TextValidator
{
public:
    virtual bool canAddChar(const mtps::str&, const char) { return true; }
    virtual bool isValidText(const mtps::str&) { return true; }
};

class TextEditorComponent final : public input::VirtualInputComponent
{
private:
    using BaseClass = input::VirtualInputComponent;

public:
    virtual void onAttached() override;

    mtps::emitter<const mtps::str&> Accepted;
    mtps::emitter<> Rejected;

    bool enabled{true};

    void setTextValidator(mtps::uptr<TextValidator> nTextValidator) noexcept;

private:
    void onKeyPressed(const input::Key&) override;

    mtps::uptr<TextValidator> m_textValidator;
    mtps::str m_originalText;
};
}  // namespace haf::scene

#endif
