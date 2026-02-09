#ifndef ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP
#define ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP

#include <haf/include/scene_components/texteditorcomponent.hpp>

import htypes;

namespace zoper
{
class HighScoreValidator : public haf::scene::TextEditorComponent::TextValidator
{
public:
    bool canAddChar(const htps::str& source, const char new_char) override;

    bool isValidText(const htps::str& source) override;
};
}  // namespace zoper

#endif
