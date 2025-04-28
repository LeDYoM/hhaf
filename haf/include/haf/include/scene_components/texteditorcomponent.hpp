HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_TEXTEDITOR_INCLUDE_HPP
#define HAF_COMPONENT_TEXTEDITOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/properties/basic_property.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/input/virtual_input_component.hpp>

namespace haf::scene
{
class TextEditorComponent final : public input::VirtualInputComponent
{
    using BaseClass = input::VirtualInputComponent;

public:
    virtual void onAttached() override;

    evt::emitter<const htps::str&> Accepted;
    evt::emitter<> Rejected;
    prop::BasicProperty<bool> DisallowReject{false};

    bool enabled{true};

    class TextValidator
    {
    public:
        virtual bool canAddChar(const htps::str&, const char) { return true; }
        virtual bool isValidText(const htps::str&) { return true; }
    };

    void setTextValidator(htps::uptr<TextValidator> nTextValidator) noexcept;

private:
    void onKeyPressed(const input::Key&) override;

    htps::uptr<TextValidator> text_validator_;
    htps::str original_text_;
};
}  // namespace haf::scene

#endif
