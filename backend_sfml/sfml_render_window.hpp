#ifndef HAF_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iinputdriver.hpp>

#include "sfml_render_target.hpp"
#include "inputdriver.hpp"

namespace haf::backend::sfmlb
{
class SFMLRenderWindow : public IWindow,
                         public SFMLRenderTarget,
                         public sf::RenderWindow
{
private:
    using BaseClass = sf::RenderWindow;
public:
    SFMLRenderWindow();
    ~SFMLRenderWindow() override;

    bool createWindow(const htps::u32 width,
                      const htps::u32 height,
                      const htps::u8 red_bpp,
                      const htps::u8 green_bpp,
                      const htps::u8 blue_bpp,
                      const htps::u8 alpha_bpp,
                      const unsigned int num_extra_parameters,
                      const unsigned int* const extra_parameters) override;

    bool isAlreadyCreated() const override;

    sf::Vector2u getSize() const override;

    bool setActive(bool active) override;

    htps::rptr<IRenderTarget> renderTarget() override;

    bool processEvents() override;
    void display() override;
    void setWindowTitle(htps::str newTitle) override;
    void closeWindow() override;

    htps::rptr<IInputDriver> inputDriver() override;
    htps::str info() const override;
    htps::str settingsInfo() override;

protected:
    virtual void onCreate();
    virtual void onResize();

private:
    bool already_created_{false};
    InputDriver input_driver_;
};

}  // namespace haf::backend::sfmlb

#endif
