HTPS_PRAGMA_ONCE
#ifndef HAF_STATES_CONTROLLER_INCLUDE_HPP
#define HAF_STATES_CONTROLLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/events/connection.hpp>
#include <htypes/include/stack.hpp>
#include <htypes/include/lockable_vector.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/component/component.hpp>

namespace haf
{
using Action = htps::function<void()>;
}

namespace haf::scene
{
/**
 * @brief Class to control states.
 * Its main use is via the StatesControllerComponent
 *
 * @tparam T
 */
template <class T>
class StatesControllerRaw
{
public:
    virtual ~StatesControllerRaw() {}

    constexpr void update()
    {
        if (!pending_actions_.current().empty())
        {
            for (auto action : pending_actions_.current())
            {
                action();
                pending_actions_.erase_value(action);
            }
            pending_actions_.update();
        }
    }

    constexpr void start(T firstState) noexcept
    {
        LogAsserter::log_assert(
            states_stack_.empty(),
            "You cannot call start if the stack is not empty");
        if (states_stack_.empty())
        {
            BeforeStart();
            push_state(htps::move(firstState));
        }
    }

    constexpr void push_state(T firstState) noexcept
    {
        postAction([this, first_state = htps::move(firstState)]() mutable {
            if (!states_stack_.empty())
            {
                StatePaused(states_stack_.back());
            }
            StatePushed(first_state);
            StateStarted(first_state);
            states_stack_.push_back(htps::move(first_state));
        });
    }

    constexpr void pop_state() noexcept
    {
        postAction([this]() {
            LogAsserter::log_assert(states_stack_.size() > 0U,
                                    "states_stack_.size() is 0");
            StateFinished(states_stack_.back());
            StatePopped(states_stack_.back());
            if (states_stack_.size() > 1U)
            {
                states_stack_.pop_back();
                StateResumed(states_stack_.back());
            }
            else
            {
                states_stack_.pop_back();
                AfterFinish();
            }
        });
    }

    constexpr void setState(T newState) { changeState(htps::move(newState)); }

    constexpr bool hasActiveState() const noexcept
    {
        return !states_stack_.empty();
    }

    constexpr htps::size_type stateStackSize() const noexcept
    {
        return states_stack_.size();
    }

    constexpr const T& currentState() const noexcept
    {
        return states_stack_.cback();
    }

    constexpr T& currentState() noexcept { return states_stack_.back(); }

    evt::emitter<const T&> StateFinished;
    evt::emitter<const T&> StateStarted;
    evt::emitter<const T&> StatePushed;
    evt::emitter<const T&> StatePopped;
    evt::emitter<const T&> StatePaused;
    evt::emitter<const T&> StateResumed;
    evt::emitter<> BeforeStart;
    evt::emitter<> AfterFinish;

private:
    inline void changeState(T newState)
    {
        postAction([this, _newState = htps::move(newState)]() {
            LogAsserter::log_assert(!states_stack_.empty(),
                                    "States stack size is empty");
            StateFinished(states_stack_.back());
            states_stack_.pop_back();
            StateStarted(_newState);
            states_stack_.push_back(htps::move(_newState));
        });
    }

    constexpr void postAction(Action action)
    {
        pending_actions_.push_back(htps::move(action));
    }

    htps::stack<T> states_stack_;
    htps::LockableVector<Action> pending_actions_;
};

template <typename T>
class StatesControllerComponent : public StatesControllerRaw<T>,
                                  public component::Component
{
public:
    ~StatesControllerComponent() override = default;

    void update() override { StatesControllerRaw<T>::update(); }
};
}  // namespace haf::scene

#endif
