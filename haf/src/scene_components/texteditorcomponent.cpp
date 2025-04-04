#include <haf/include/scene_components/texteditorcomponent.hpp>
#include <haf/include/scene_components/text.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/input/key.hpp>

using namespace htps;

namespace haf::scene
{
void TextEditorComponent::onAttached()
{
    BaseClass::onAttached();

    using namespace haf::scene::nodes;

    auto attached_text_node{attachedNode()->component<Text>()};
    original_text_           = attached_text_node->Text();
    attached_text_node->Text = "";
}

void TextEditorComponent::onKeyPressed(const input::Key& key)
{
    using namespace nodes;
    using namespace input;

    if (enabled)
    {
        auto attached_text_node{attachedNode()->componentOfType<Text>()};
        if (isAscii(key))
        {
            char const c_ascii{this->toAscii(key)};
            bool success{true};
            if (text_validator_)
            {
                success = text_validator_->canAddChar(
                    attached_text_node->Text(), c_ascii);
            }

            if (success)
            {
                str new_text{attached_text_node->Text()};
                new_text.push_back(c_ascii);
                attached_text_node->Text = htps::move(new_text);
            }
        }
        else if (key == Key::BackSpace && !attached_text_node->Text().empty())
        {
            attached_text_node->Text = attached_text_node->Text().substr(
                0U, attached_text_node->Text().size() - 1U);
        }
        else if (key == Key::Return)
        {
            bool success{true};
            if (text_validator_)
            {
                success =
                    text_validator_->isValidText(attached_text_node->Text());
            }
            if (success)
            {
                enabled = false;
                Accepted(attached_text_node->Text());
            }
        }
        else if (key == Key::Escape)
        {
            attached_text_node->Text = original_text_;
            enabled                  = false;
            Rejected();
        }
    }
}

void TextEditorComponent::setTextValidator(
    htps::uptr<TextValidator> nTextValidator) noexcept
{
    std::swap(text_validator_, nTextValidator);
}

}  // namespace haf::scene
