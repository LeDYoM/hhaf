#include "randomnumberscomponent.hpp"
#include <lib/random/i_include/randomsystem.hpp>

#include <lib/include/liblog.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace lib::rnd
{
class RandomNumbersComponent::RandomNumbersComponentPrivate
{
public:
    constexpr RandomNumbersComponentPrivate(sys::RandomSystem &random_system) noexcept
        : random_system_{random_system}
    {
        log_assert(std::addressof(random_system_) != nullptr, "nullptr RandomSystem received");
    }

    ~RandomNumbersComponentPrivate() = default;

    const mtps::str&name() const noexcept { return name_; }
    void setName(mtps::str name) { std::swap(name, name_); }

    sys::RandomSystem &randomsystem() noexcept { return random_system_; }

private:
    sys::RandomSystem &random_system_;
    mtps::str name_;
};

RandomNumbersComponent::RandomNumbersComponent() noexcept : priv_{nullptr} {}

RandomNumbersComponent::~RandomNumbersComponent() = default;

void RandomNumbersComponent::setName(mtps::str new_name)
{
    priv_->setName(std::move(new_name));
}

const mtps::str&RandomNumbersComponent::name() const noexcept
{
    return priv_->name();
}

mtps::u32 RandomNumbersComponent::getUInt(const mtps::size_type max, const mtps::size_type min) const
{
    DisplayLog::info("Asked for random number between ", min, " and ", max);

    log_assert(min != max, "The min and max parameters must be different");
    log_assert(max > min, "The max paramter must be greater than min");

    const auto next(priv_->randomsystem().getNext(name(), min, max));
    DisplayLog::verbose("Fetch next element from queue: ", next);
    const mtps::size_type generated(next % (max - min));
    DisplayLog::verbose("\tGot ", generated);
    DisplayLog::info("\tReturning ", min + generated);
    return min + generated;
}

void RandomNumbersComponent::onAttached()
{
    if (attachedNode())
    {
        priv_ = mtps::muptr<RandomNumbersComponentPrivate>(
            sys::getSystem<sys::RandomSystem>(attachedNode()));
    }
}
} // namespace lib::rnd
