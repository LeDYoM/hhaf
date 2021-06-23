#include "highscorevalidator.hpp"

namespace zoper
{
bool HighScoreValidator::canAddChar(const htps::str& source,
                                    const char new_char)
{
    htps::str dest{source};
    dest.push_back(new_char);
    return isValidText(dest);
    return true;
}

bool HighScoreValidator::isValidText(const htps::str& source)
{
    return source.size() < 4U;
}
}  // namespace zoper
