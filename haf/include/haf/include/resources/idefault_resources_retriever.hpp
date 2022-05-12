HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_IDEFAULT_RESOURCE_RETRIVER_INCLUDE_HPP
#define HAF_RESOURCES_IDEFAULT_RESOURCE_RETRIVER_INCLUDE_HPP

#include <htypes/include/types.hpp>

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
    virtual htps::sptr<res::IShader> getDefaultShader() const = 0;
};

}  // namespace haf::res

#endif
