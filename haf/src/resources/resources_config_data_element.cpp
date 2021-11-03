#include "resources/resources_config_data_element.hpp"

namespace haf::res
{
bool ResourcesConfigDataElement::deserialize(htps::Object const& obj)
{
    type      = obj[ResourcesConfigDataElement::TypeStr].getValue();
    file_name = obj[ResourcesConfigDataElement::FileNameStr].getValue();
    return true;
}

}  // namespace haf::res
