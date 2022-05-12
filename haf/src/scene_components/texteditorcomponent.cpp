#include <haf/include/scene_components/texteditorcomponent.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/input/key.hpp>

using namespace htps;

namespace haf::scene
{
void TextEditorComponent::onAttached()
{
    BaseClass::onAttached();

    using namespace haf::scene::nodes;

    auto& text_prop(attachedNodeAs<nodes::SceneNodeText>()
                        ->prop<nodes::SceneNodeTextProperties>());
    original_text_ = text_prop.get<Text>();
    text_prop.set<Text>("");
}

void TextEditorComponent::onKeyPressed(const input::Key& key)
{
    using namespace nodes;
    using namespace input;

    if (enabled)
    {
        auto& text_prop(attachedNodeAs<nodes::SceneNodeText>()
                            ->prop<nodes::SceneNodeTextProperties>());
        if (isAscii(key))
        {
            const char c_ascii{this->toAscii(key)};
            bool success{true};
            if (text_validator_)
            {
                success =
                    text_validator_->canAddChar(text_prop.get<Text>(), c_ascii);
            }

            if (success)
            {
                str new_text{text_prop.get<Text>()};
                new_text.push_back(c_ascii);
                text_prop.set<Text>(htps::move(new_text));
            }
        }
        else if (key == Key::BackSpace && !text_prop.get<Text>().empty())
        {
            text_prop.set<Text>(text_prop.get<Text>().substr(
                0U, text_prop.get<Text>().size() - 1));
        }
        else if (key == Key::Return)
        {
            bool success{true};
            if (text_validator_)
            {
                success = text_validator_->isValidText(text_prop.get<Text>());
            }
            if (success)
            {
                enabled = false;
                Accepted(text_prop.get<Text>());
            }
        }
        else if (key == Key::Escape)
        {
            text_prop.set<Text>(original_text_);
            enabled = false;
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
