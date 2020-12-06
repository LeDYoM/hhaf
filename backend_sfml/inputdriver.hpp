#ifndef HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <backend_dev/include/iinputdriver.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>

namespace haf::backend::sfmlb
{
class InputDriver : public IInputDriver
{
public:
    InputDriver()           = default;
    ~InputDriver() override = default;

    bool arePendingKeyPresses() const override;
    bool arePendingKeyReleases() const override;

    iKey popKeyPress() override;
    iKey popKeyRelease() override;

    void keyPressed(const iKey) override;
    void keyReleased(const iKey) override;

    void keyEvent(const sf::Event& e);

    std::queue<iKey> keysPressed_;
    std::queue<iKey> keysReleased_;
};
}  // namespace haf::backend::sfmlb

#endif
