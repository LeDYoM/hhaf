export module mc_serial:serializer;

import :object;
import :object_parser;
import htypes;

namespace mcs
{
namespace tps = htps;

template <typename T>
class Serializer
{
public:
    static constexpr tps::str serialize(T const& data)
    {
        Object obj;
        obj << data;

        tps::str temp;
        temp << obj;
        return temp;
    }

    static constexpr bool deserialize(tps::str const& data, T& output)
    {
        ObjectCompiler obj_compiler(data);
        if (obj_compiler.compile())
        {
            // The compilation was correct so, at least we
            // have a valid Object.
            obj_compiler.result() >> output;
            return true;
        }
        return false;
    }
};

}  // namespace mcs
