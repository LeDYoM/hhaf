#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/iboardmodelactuator.hpp>
#include <boardmanager/include/itile.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::board;

TEST_CASE("BoardManager of size 0,0", "[board_manager]")
{
    BoardModelComponent board_model_component;

    // Test default constucted is 0 sized.
    CHECK(board_model_component.size() == vector2dst{0U, 0U});

    board_model_component.initialize(vector2dst{0U, 0U}, nullptr);
    CHECK(board_model_component.size() == vector2dst{0U, 0U});
}