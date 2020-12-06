#ifndef ZOPER_SCOREUTILS_INCLUDE_HPP
#define ZOPER_SCOREUTILS_INCLUDE_HPP

#include <mtypes/include/types.hpp>

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
    ScoreIncrementer(mtps::sptr<LevelProperties> level_properties);

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
    mtps::size_type hits_{0U};
    mtps::sptr<LevelProperties> level_properties_;
};
} // namespace zoper

#endif
