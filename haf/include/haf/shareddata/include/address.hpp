#pragma once

#ifndef HAF_SHAREDDATA_ADRESS_INCLUDE_HPP
#define HAF_SHAREDDATA_ADRESS_INCLUDE_HPP

#include <mtypes/include/p_impl_pointer.hpp>
#include <mtypes/include/str.hpp>

namespace haf::shdata
{
class Address
{
public:
    explicit Address(mtps::str const& addr, char const separator = '/');
private:
    struct AddressPrivate;
    mtps::PImplPointer<AddressPrivate> private_;
};
}  // namespace haf::shdata

#endif
