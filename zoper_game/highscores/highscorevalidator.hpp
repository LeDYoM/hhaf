#ifndef ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP
#define ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/scene_components/texteditorcomponent.hpp>

namespace zoper
{
class HighScoreValidator : public haf::scene::TextValidator
{
public:
    bool canAddChar(const htps::str &source, const char new_char) override
    {
        htps::str dest{source};
        dest.push_back(new_char);
        return isValidText(dest);
        return true;
    }

    bool isValidText(const htps::str &source) override
    {
        return source.size() < 4U;
    }
};
} // namespace zoper

#endif
