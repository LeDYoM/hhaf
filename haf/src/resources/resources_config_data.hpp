#ifndef HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/object.hpp>
#include <htypes/include/vector.hpp>

#include <haf/include/shareddata/ishareable.hpp>

#include "resources/resources_config_data_element.hpp"

namespace haf::res
{
struct HAF_PRIVATE ResourcesConfigData : public data::IDeserializable
{
    htps::Dictionary<htps::vector<ResourcesConfigDataElement>> elements;
    bool deserialize(htps::Object const& obj) override;
};

}  // namespace haf::res

#endif
