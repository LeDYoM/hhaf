#ifndef ZOPER_SCOREUTILS_INCLUDE_HPP
#define ZOPER_SCOREUTILS_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace zoper
{
class LevelProperties;

/**
 * @brief Class to help the logic of incrementing the score.
 * This class uses RAII to store a pointer to @b LevelProperties
 * and increment the score on destruction by calling it.
 */
class ScoreIncrementer
{
public:
    /**
     * @brief Construct a new Score Incrementer object
     *
     * @param level_properties
     */
    ScoreIncrementer(htps::sptr<LevelProperties> level_properties);
    ScoreIncrementer(ScoreIncrementer&) = delete;

    /**
     * @brief Destroy the Score Incrementer object
     *
     */
    ~ScoreIncrementer();

    /**
     * @brief Increments the number of token hit.
     */
    void addHit();

private:
    htps::size_type hits_{0U};
    htps::sptr<LevelProperties> level_properties_;
};
}  // namespace zoper

#endif
