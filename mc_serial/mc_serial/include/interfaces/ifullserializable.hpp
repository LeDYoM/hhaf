MCS_PRAGMA_ONCE
#ifndef MCS_IFULLSERIALIZABLE_INCLUDE_HPP
#define MCS_IFULLSERIALIZABLE_INCLUDE_HPP

#include <mc_serial/include/interfaces/iserializable.hpp>
#include <mc_serial/include/interfaces/ideserializable.hpp>

namespace mcs
{
class IFullSerializable : public ISerializable, public IDeserializable
{};
}  // namespace mcs

#endif
