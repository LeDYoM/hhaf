HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP

#include "haf_private.hpp"
import htypes;

#include <haf/include/data/ideserializable.hpp>

#include "resources/resources_config_data_element.hpp"

namespace haf::res
{
struct HAF_PRIVATE ResourcesConfigData
    : public data::DeserializableDictionary<
          data::DeserializableDictionary<ResourcesConfigDataElement>>
{};

}  // namespace haf::res

#endif
