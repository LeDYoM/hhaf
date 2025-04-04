MCS_PRAGMA_ONCE
#ifndef MCS_TEXT_SERIALIZER_INCLUDE_HPP
#define MCS_TEXT_SERIALIZER_INCLUDE_HPP

#include <mc_serial/include/object.hpp>
#include <mc_serial/include/object_parser.hpp>
#include <mc_serial/include/interfaces/iserializable.hpp>
#include <htypes/include/str.hpp>

namespace mcs
{
namespace tps = htps;

class TextSerializer
{
public:
    bool deserializeFromText(tps::str const& text_data, IDeserializable& data)
    {
        ObjectCompiler obj_compiler(text_data);
        if (obj_compiler.compile())
        {
            // The compilation was correct so, at least we
            // have a valid Object.
            return data.deserialize(obj_compiler.result());
        }
        else
        {
            return false;
        }
    }

    bool serializeToText(tps::str& data_str, ISerializable const& data)
    {
        Object obj;
        auto const temp{data.serialize(obj)};

        if (temp)
        {
            data_str.clear();
            data_str << obj;

            return true;
        }
        return false;
    }
};

}  // namespace mcs

#endif
