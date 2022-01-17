#include "resources/resources_config_data_element.hpp"

namespace haf::res
{
bool ResourcesConfigDataElement::deserialize(htps::Object const& obj)
{
    bool result{true};
    result &= obj[ResourcesConfigDataElement::TypeStr].as(type);
    result &= obj[ResourcesConfigDataElement::FileNameStr].as(file_name);
    return result;
}

}  // namespace haf::res
