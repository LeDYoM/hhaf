HTPS_PRAGMA_ONCE
#ifndef HTYPES_HASH_TABLE_INCLUDE_HPP
#define HTYPES_HASH_TABLE_INCLUDE_HPP

#include <htypes/include/basic_dictionary.hpp>
#include <htypes/include/str.hpp>

namespace htps
{
/**
 * @brief This class contains a group of keys and their associated values.
 * @tparam T Type of the values stored
 */
template <typename T>
using HashTable = BasicDictionary<u32, T>;

}  // namespace htps

#endif
