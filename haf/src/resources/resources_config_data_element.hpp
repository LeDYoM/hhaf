HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCES_CONFIG_DATA_ELEMENT_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIG_DATA_ELEMENT_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <facil_math/include/rect.hpp>

#include <haf/include/shareddata/ishareable.hpp>
#include "resource_data_description_names.hpp"

namespace haf::res
{
struct HAF_PRIVATE ResourcesConfigDataElement : public data::IDeserializable
{
    htps::str type;
    htps::str file_name;
    static constexpr auto const TypeStr{ResourceTypeStr};
    static constexpr auto FileNameStr{ResourceFileNameStr};

    bool deserialize(mcs::Object const& obj) override;
};

}  // namespace haf::res

#endif
