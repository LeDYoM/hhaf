#include "randomnumberscomponent.hpp"
#include <lib/system/randomsystem.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/scenenode.hpp>

namespace lib::scene
{
class RandomNumbersComponent::RandomNumbersComponentPrivate
{
public:
    constexpr RandomNumbersComponentPrivate(core::RandomSystem &random_system) noexcept
        : random_system_{random_system}
    {
        assert_debug(std::addressof(random_system_) != nullptr, "nullptr RandomSystem received");
    }

    ~RandomNumbersComponentPrivate() = default;

    const str &name() const noexcept { return name_; }
    void setName(str name) { std::swap(name, name_); }

    core::RandomSystem &randomsystem() noexcept { return random_system_; }

private:
    core::RandomSystem &random_system_;
    str name_;
};

RandomNumbersComponent::RandomNumbersComponent() noexcept : priv_{nullptr} {}

RandomNumbersComponent::~RandomNumbersComponent() = default;

void RandomNumbersComponent::setName(str new_name)
{
    priv_->setName(std::move(new_name));
}

const str &RandomNumbersComponent::name() const noexcept
{
    return priv_->name();
}

u32 RandomNumbersComponent::getUInt(const size_type max, const size_type min) const
{
    log_debug_info("Asked for random number between ", min, " and ", max);

    assert_release(min != max, "The min and max parameters must be different");
    assert_release(max > min, "The max paramter must be greater than min");

    const auto next(priv_->randomsystem().getNext(name(), min, max));
    log_debug_info("Fetch next element from queue: ", next);
    const size_type generated(next % (max - min));
    log_debug_info("\tGot ", generated);
    log_debug_info("\tReturning ", min + generated);
    return min + generated;
}

void RandomNumbersComponent::onAttached()
{
    if (attachedNode())
    {
        priv_ = muptr<RandomNumbersComponentPrivate>(attachedNode()
                                                        ->randomSystem());
    }
}
} // namespace lib::scene
