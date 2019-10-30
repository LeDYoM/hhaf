#pragma once

#ifndef LIB_DATA_PROVIDER_COMPONENT_INCLUDE_HPP
#define LIB_DATA_PROVIDER_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/components/icomponent.hpp>

namespace lib::scene
{
    /**
    * This component class is intended to be used to generate
    * a series of random numbers.
    */
    class DataProviderComponent final : public IComponent
    {
    public:
        DataProviderComponent() noexcept;
        ~DataProviderComponent() override;
        u32 getUInt(const size_type max, const size_type min = 0U) const;
        void setName(str new_name);
        const str& name() const noexcept;

        void onAttached() override;
    private:
        class DataProviderComponentPrivate;
        uptr<DataProviderComponentPrivate> priv_;
	};
}

#endif
