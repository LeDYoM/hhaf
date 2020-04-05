#pragma once

#ifndef LIB_DATA_PROVIDER_COMPONENT_INCLUDE_HPP
#define LIB_DATA_PROVIDER_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/include/icomponent.hpp>

namespace haf::rnd
{
/**
* @brief This component class is intended to be used to generate
* a series of random numbers.
*/
class RandomNumbersComponent final : public scene::IComponent
{
public:
    RandomNumbersComponent() noexcept;
    ~RandomNumbersComponent() override;
    mtps::u32 getUInt(const mtps::size_type max, const mtps::size_type min = 0U) const;
    void setName(mtps::str new_name);
    const mtps::str&name() const noexcept;

    void onAttached() override;

private:
    class RandomNumbersComponentPrivate;
    mtps::uptr<RandomNumbersComponentPrivate> priv_;
};
} // namespace haf::rnd

#endif
