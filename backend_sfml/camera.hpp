#ifndef HAF_BACKEND_SFMLB_CAMERA_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_CAMERA_INCLUDE_HPP

#include <backend_dev/include/icamera.hpp>
#include <SFML/Graphics/View.hpp>

namespace haf::backend::sfmlb
{
class Camera : public ICamera
{
public:
    void setPointOfView(htps::vector2df const& pov) override;
    void setViewPort(htps::Rectf32 const& viewPort) override;
    void setNearRect(htps::Rectf32 const& nearRect) override;
    void setFarRect(htps::Rectf32 const& nearRect) override;
private:
    sf::View view_;
};
}  // namespace haf::backend::sfmlb

#endif
