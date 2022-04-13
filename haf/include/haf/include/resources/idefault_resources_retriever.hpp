#ifndef HAF_RESOURCES_IDEFAULT_RESOURCE_RETRIVER_INCLUDE_HPP
#define HAF_RESOURCES_IDEFAULT_RESOURCE_RETRIVER_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

namespace haf::res
{
class IFont;
class ITTFont;
class ITexture;
class IShader;

class IDefaultResourcesRetriever
{
protected:
    ~IDefaultResourcesRetriever() = default;
public:
    virtual types::sptr<res::IShader> getDefaultShader() const = 0;
};

}  // namespace haf::res

#endif
