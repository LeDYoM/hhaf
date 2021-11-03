#ifndef HAF_RESOURCES_RESOURCES_CONFIG_DATA_ELEMENT_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIG_DATA_ELEMENT_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/object.hpp>

#include <haf/include/shareddata/ishareable.hpp>

namespace haf::res
{
struct HAF_PRIVATE ResourcesConfigDataElement : public data::IDeserializable
{
    htps::str name;
    htps::str type;
    htps::str file_name;
    static constexpr char TypeStr[]     = "type";
    static constexpr char FileNameStr[] = "file";

    bool deserialize(htps::Object const& obj) override;
};

}  // namespace haf::res

#endif
