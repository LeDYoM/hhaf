#ifndef HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/object.hpp>

#include <haf/include/shareddata/ishareable.hpp>

namespace haf::res
{
struct ResourcesConfigDataElement : public data::IDeserializable
{
    htps::str name;
    htps::str type;
    htps::str file_name;
    static constexpr char TypeStr[]     = "type";
    static constexpr char FileNameStr[] = "file";

    bool deserialize(htps::Object const& obj) override
    {
        type      = obj[ResourcesConfigDataElement::TypeStr].getValue();
        file_name = obj[ResourcesConfigDataElement::FileNameStr].getValue();
        return true;
    }
};

inline const htps::Object& operator>>(const htps::Object& obj,
                                      ResourcesConfigDataElement& element)
{
    element.type      = obj[ResourcesConfigDataElement::TypeStr].getValue();
    element.file_name = obj[ResourcesConfigDataElement::FileNameStr].getValue();

    return obj;
}

struct ResourcesConfigData
{
    htps::Dictionary<htps::vector<ResourcesConfigDataElement>> elements;
};

inline const htps::Object& operator>>(const htps::Object& obj,
                                      ResourcesConfigData& elements)
{
    for (auto const& section : obj.objects())
    {
        htps::vector<ResourcesConfigDataElement> temp_section;
        for (auto const& element : section.second.objects())
        {
            ResourcesConfigDataElement temp;
            temp.name = element.first;
            temp.deserialize(element.second);
            temp_section.push_back(std::move(temp));
        }
        elements.elements.add(section.first, std::move(temp_section));
    }
    return obj;
}

}  // namespace haf::res

#endif
