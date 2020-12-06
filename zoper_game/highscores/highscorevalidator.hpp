#ifndef ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP
#define ZOPER_HIGHSCORE_VALIDATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <haf/scene_components/include/texteditorcomponent.hpp>

namespace zoper
{
class HighScoreValidator : public haf::scene::TextValidator
{
public:
    bool canAddChar(const mtps::str &source, const char new_char) override
    {
        mtps::str dest{source};
        dest.append_char(new_char);
        return isValidText(dest);
        return true;
    }

    bool isValidText(const mtps::str &source) override
    {
        return source.size() < 4U;
    }
};
} // namespace zoper

#endif
