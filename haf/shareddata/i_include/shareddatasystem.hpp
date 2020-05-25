#pragma once

#ifndef HAF_SYSTEM_SHARED_DATA_INCLUDE_HPP
#define HAF_SYSTEM_SHARED_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <system/i_include/appservice.hpp>
#include <haf/shareddata/include/ishareable.hpp>

namespace haf::sys
{
/**
 * @brief Thisis a system whose only purpose is to store data shared
 * between different objects on the system.
 */
class SharedDataSystem final : public AppService
{
public:
    /**
     * @see AppService::AppService
     */
    SharedDataSystem(sys::SystemProvider& system_provider) noexcept;

    /**
     * @brief Destroy the Shared Data System object
     */
    ~SharedDataSystem() override;

    bool store(mtps::uptr<shdata::IShareable> data) noexcept;
    [[nodiscard]] mtps::uptr<shdata::IShareable> retrieve() noexcept;

    bool isEmpty() const noexcept;
    bool makeEmpty();

    const mtps::uptr<shdata::IShareable>& view() const noexcept;

private:
    mtps::uptr<shdata::IShareable> data_;
};

}  // namespace haf::sys

#endif
