#ifndef HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <htypes/include/vector.hpp>
#include <backend_dev/include/iinputdriver.hpp>
#include <SFML/Window/Event.hpp>

namespace haf::backend::sfmlb
{
class SFMLInputDriver : public IInputDriver
{
public:
    SFMLInputDriver();
    ~SFMLInputDriver() override;

    void keyPressed(IKey const) override;
    void keyReleased(IKey const) override;

    void keyEvent(sf::Event const& e);

    void clearInternalInputBuffer() override;
    void readKeyPressed(htps::vector<IKey>& keys_pressed) const override;
    void readKeyReleased(htps::vector<IKey>& keys_released) const override;

private:
    htps::vector<IKey> keys_pressed_;
    htps::vector<IKey> keys_released_;
};
}  // namespace haf::backend::sfmlb

#endif
