export module htypes:dictionary;

import :bdictionary;
import :str;

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
