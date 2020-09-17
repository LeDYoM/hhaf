#include "address.hpp"
#include <mtypes/include/vector.hpp>

using namespace mtps;

namespace haf::shdata
{
    struct Address::AddressPrivate
    {
        AddressPrivate()
        {
            
        }
        vector<str> adress_parts_;
    };

Address::Address(str const& addr, char const separator)
    : private_{make_pimplp<AddressPrivate>()}
{

}

}  // namespace haf::sys
