HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCES_CONFIG_DATA_ELEMENT_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIG_DATA_ELEMENT_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/object.hpp>

#include <haf/include/shareddata/ishareable.hpp>
#include "resource_data_description_names.hpp"

namespace haf::res
{
struct HAF_PRIVATE ResourcesConfigDataElement : public data::IDeserializable
{
    htps::str type;
    htps::str file_name;
    static constexpr char TypeStr[5U]     = ResourceTypeStr;
    static constexpr char FileNameStr[5U] = ResourceFileNameStr;

    bool deserialize(htps::Object const& obj) override;
};

}  // namespace haf::res

#endif
