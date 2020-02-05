#pragma once

#ifndef ZOPER_SCOREUTILS_INCLUDE_HPP
#define ZOPER_SCOREUTILS_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace zoper
{
class LevelProperties;

/// Class to help the logic of incrementing the score.
/// This class uses RAII to store a pointer to @b LevelProperties
/// and increment the score on destruction by calling it.
class ScoreIncrementer
{
public:
    /// Constructor.
    /// @param level_properties class where to forward score increments.
    ScoreIncrementer(lib::sptr<LevelProperties> level_properties);

    /// destructor that perform the score incrementation.
    ~ScoreIncrementer();

    /// Increments the number of token hit.
    void addHit();

private:
    lib::size_type hits_{0U};
    lib::sptr<LevelProperties> level_properties_;
};
} // namespace zoper

#endif
