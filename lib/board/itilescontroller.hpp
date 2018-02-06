#ifndef __LIB_ITILESCONTROLLER_HPP__
#define __LIB_ITILESCONTROLLER_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>

namespace lib
{
    namespace board
    {
        using BoardTileData = s32;

        class ITile : public PropertyTrigger<BoardTileData>
        {
        public:
            using PropertyTrigger<BoardTileData>::PropertyTrigger;
            virtual ~ITile() = default;
        };

        using SITilePointer = sptr<ITile>;
    }
}

#endif
