#pragma once

#ifndef HAF_SYSTEM_SHARED_DATA_INCLUDE_HPP
#define HAF_SYSTEM_SHARED_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/appservice.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include <haf/shareddata/include/ishareddatasystem.hpp>

namespace haf::sys
{

/// SharedDataSystem is a system whose only purpose is to store
/// data shared between different objects.
class SharedDataSystem final : public AppService, public ISharedDataSystem
{
public:
    /**
     * @brief Default constructor
     */
    SharedDataSystem(sys::SystemProvider& system_provider) noexcept;
    ~SharedDataSystem() override;

    void store(mtps::uptr<shdata::IShareable> data) noexcept override;
    [[nodiscard]] mtps::uptr<shdata::IShareable> retrieve() noexcept override;

    bool isEmpty() const noexcept override;
    bool makeEmpty() override;

private:
    mtps::uptr<shdata::IShareable> data_;
};
} // namespace haf::sys

#endif
