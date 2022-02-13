#ifndef HAF_BACKEND_DEV_ICAMERA_INCLUDE_HPP
#define HAF_BACKEND_DEV_ICAMERA_INCLUDE_HPP

#include <htypes/include/rect.hpp>
#include <htypes/include/vector2d.hpp>

namespace haf::backend
{
class ICamera
{
protected:
    virtual ~ICamera() = default;

public:
    virtual void setPointOfView(htps::vector2df const& pov) = 0;
    virtual void setNearRect(htps::Rectf32 const& nearRect) = 0;
    virtual void setFarRect(htps::Rectf32 const& nearRect) = 0;
};
}  // namespace haf::backend

#endif
