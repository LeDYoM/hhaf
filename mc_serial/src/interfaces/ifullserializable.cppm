export module mc_serial:ifull_serializable;

import :iserializable;
import :ideserializable;

namespace mcs
{
class IFullSerializable : public ISerializable, public IDeserializable
{};
}  // namespace mcs
