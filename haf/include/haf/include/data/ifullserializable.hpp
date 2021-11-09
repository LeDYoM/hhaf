#ifndef HAF_DATA_IFULLSERIALIZABLE_INCLUDE_HPP
#define HAF_DATA_IFULLSERIALIZABLE_INCLUDE_HPP

#include <haf/include/data/iserializable.hpp>
#include <haf/include/data/ideserializable.hpp>

namespace haf::data
{
class IFullSerializable : public ISerializable, public IDeserializable
{};
}  // namespace haf::data

#endif
