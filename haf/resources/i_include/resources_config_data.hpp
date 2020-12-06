#ifndef HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCES_CONFIG_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/object.hpp>

namespace haf::res
{
struct ResourcesConfigDataElement
{
    mtps::str type;
    mtps::str file_name;

    static constexpr char TypeStr[]     = "type";
    static constexpr char FileNameStr[] = "filename";
};

inline const mtps::Object& operator>>(const mtps::Object& obj,
                                      ResourcesConfigDataElement& element)
{
    element.type      = obj[ResourcesConfigDataElement::TypeStr].getValue();
    element.file_name = obj[ResourcesConfigDataElement::FileNameStr].getValue();

    return obj;
}

struct ResourcesConfigData
{
    mtps::Object elements_;
};

inline const mtps::Object& operator>>(const mtps::Object& obj,
                                      ResourcesConfigData& element)
{
    element.elements_ = obj;
    return obj;
}

}  // namespace haf::res

#endif
