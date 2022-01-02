#ifndef HAF_DATA_PROVIDER_RANDOM_NUMBERS_COMPONENT_INCLUDE_HPP
#define HAF_DATA_PROVIDER_RANDOM_NUMBERS_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/component/component.hpp>

namespace haf::rnd
{
/**
 * @brief This component class is intended to be used to generate
 * a series of random numbers.
 * @see component::IComponent
 */
class RandomNumbersComponent final : public component::Component
{
public:
    RandomNumbersComponent() noexcept;
    ~RandomNumbersComponent() override;
    htps::u32 getUInt(htps::size_type const max,
                      htps::size_type const min = 0U) const;
    void setName(htps::str new_name);
    const htps::str& name() const noexcept;

    void onAttached() override;

private:
    class RandomNumbersComponentPrivate;
    htps::uptr<RandomNumbersComponentPrivate> priv_;
};
}  // namespace haf::rnd

#endif
