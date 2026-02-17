export module haf:data:ifullserializable;

import :data:ideserializable;
import :data:iserializable;

namespace haf::data
{
class IFullSerializable : public ISerializable, public IDeserializable
{};
}  // namespace haf::data
