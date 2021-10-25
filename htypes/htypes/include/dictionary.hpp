#ifndef HTYPES_DICTIONARY_INCLUDE_HPP
#define HTYPES_DICTIONARY_INCLUDE_HPP

#include <htypes/include/basic_dictionary.hpp>
#include <htypes/include/str.hpp>

namespace htps
{
/**
 * @brief This class contains a group of keys and their associated values.
 * @tparam T Type of the values stored
 */
template <typename T>
using Dictionary = BasicDictionary<str, T>;

using PureDictionary = Dictionary<str>;

}  // namespace htps

#endif
