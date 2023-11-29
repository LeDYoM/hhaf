HAF_PRAGMA_ONCE
#ifndef HAF_SHAREDDATA_ISHAREABLE_INCLUDE_HPP
#define HAF_SHAREDDATA_ISHAREABLE_INCLUDE_HPP

#include <haf/include/data/types.hpp>

namespace haf::shdata
{
class IShareable : public data::IFullSerializable
{};

}  // namespace haf::shdata

#endif
