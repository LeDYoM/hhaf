#ifndef HAF_BACKEND_DEV_CAMERA_DATA_INCLUDE_HPP
#define HAF_BACKEND_DEV_CAMERA_DATA_INCLUDE_HPP

#include <htypes/include/rect.hpp>
#include <htypes/include/vector2d.hpp>

namespace haf::backend
{
struct CameraData
{
    htps::vector2df pov;
    htps::Rectf32 viewPort;
    htps::Rectf32 nearRect;
    htps::Rectf32 farRect;
    bool update_required;
};

}  // namespace haf::backend

#endif
