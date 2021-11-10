#include "resources/resources_config_data.hpp"
#include <htypes/include/str.hpp>

using namespace htps;

namespace haf::res
{
/*
bool ResourcesConfigData::deserialize(htps::Object const& obj)
{
    for (auto const& section : obj.objects())
    {
        vector<ResourcesConfigDataElement> temp_section;
        for (auto const& element : section.second.objects())
        {
            ResourcesConfigDataElement temp;
            temp.name = element.first;
            temp.deserialize(element.second);
            temp_section.push_back(std::move(temp));
        }
        elements.add(section.first, std::move(temp_section));
    }
    return true;
}
*/
}  // namespace haf::res
