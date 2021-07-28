#ifndef HAF_STATES_CONTROLLER_INCLUDE_HPP
#define HAF_STATES_CONTROLLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/connection.hpp>
#include <htypes/include/stack.hpp>
#include <htypes/include/lockablevector.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/components/icomponent.hpp>

namespace haf
{
using Action = htps::function<void()>;
}

namespace haf::scene
{
template <class T>
class StatesControllerRaw
{
public:
    virtual ~StatesControllerRaw() {}

    constexpr void update()
    {
        if (!m_pendingActions.current().empty())
        {
            for (auto action : m_pendingActions.current())
            {
                action();
                m_pendingActions.erase_value(action);
            }
            m_pendingActions.update();
        }
    }

    constexpr void start(T firstState) noexcept
    {
        LogAsserter::log_assert(
            m_statesStack.empty(),
            "You cannot call start if the stack is not empty");
        if (m_statesStack.empty())
        {
            BeforeStart();
            push_state(std::move(firstState));
        }
    }

    constexpr void push_state(T firstState) noexcept
    {
        postAction([this, first_state = std::move(firstState)]() mutable {
            if (!m_statesStack.empty())
            {
                StatePaused(m_statesStack.back());
            }
            StatePushed(first_state);
            StateStarted(first_state);
            m_statesStack.push_back(std::move(first_state));
        });
    }

    constexpr void pop_state() noexcept
    {
        postAction([this]() {
            LogAsserter::log_assert(m_statesStack.size() > 0U,
                                    "m_statesStack.size() is 0");
            StateFinished(m_statesStack.back());
            StatePopped(m_statesStack.back());
            if (m_statesStack.size() > 1U)
            {
                m_statesStack.pop_back();
                StateResumed(m_statesStack.back());
            }
            else
            {
                m_statesStack.pop_back();
                AfterFinish();
            }
        });
    }

    constexpr void setState(T newState) { changeState(std::move(newState)); }

    constexpr bool hasActiveState() const noexcept
    {
        return !m_statesStack.empty();
    }

    constexpr htps::size_type stateStackSize() const noexcept
    {
        return m_statesStack.size();
    }

    constexpr const T& currentState() const noexcept
    {
        return m_statesStack.cback();
    }

    constexpr T& currentState() noexcept { return m_statesStack.back(); }

    htps::emitter<const T&> StateFinished;
    htps::emitter<const T&> StateStarted;
    htps::emitter<const T&> StatePushed;
    htps::emitter<const T&> StatePopped;
    htps::emitter<const T&> StatePaused;
    htps::emitter<const T&> StateResumed;
    htps::emitter<> BeforeStart;
    htps::emitter<> AfterFinish;

private:
    inline void changeState(T newState)
    {
        postAction([this, newState = std::move(newState)]() {
            LogAsserter::log_assert(m_statesStack.size() != 0U,
                                    "States stack size is 0");
            StateFinished(m_statesStack.back());
            m_statesStack.pop_back();
            StateStarted(newState);
            m_statesStack.push_back(std::move(newState));
        });
    }

    constexpr void postAction(Action action)
    {
        m_pendingActions.push_back(std::move(action));
    }

    htps::stack<T> m_statesStack;
    htps::LockableVector<Action> m_pendingActions;
};

template <typename T>
class StatesController : public StatesControllerRaw<T>, public component::IComponent
{
public:
    ~StatesController() override {}

    void update() override { StatesControllerRaw<T>::update(); }
};
}  // namespace haf::scene

#endif
