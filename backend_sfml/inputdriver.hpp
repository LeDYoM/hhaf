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

    IKey popKeyPress() override;
    IKey popKeyRelease() override;

    void keyPressed(const IKey) override;
    void keyReleased(const IKey) override;

    void keyEvent(const sf::Event& e);

    std::queue<IKey> keysPressed_;
    std::queue<IKey> keysReleased_;
};
}  // namespace haf::backend::sfmlb

#endif
