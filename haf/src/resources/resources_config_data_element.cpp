#include "resources/resources_config_data_element.hpp"

namespace haf::res
{
bool ResourcesConfigDataElement::deserialize(mcs::Object const& obj)
{
    bool result{true};
    result &= obj[htps::str{ResourcesConfigDataElement::TypeStr}].as(type);
    result &= obj[htps::str{ResourcesConfigDataElement::FileNameStr}].as(file_name);
    return result;
}

}  // namespace haf::res
