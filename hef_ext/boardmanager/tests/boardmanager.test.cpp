#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/iboardmodelactuator.hpp>
#include <boardmanager/include/itile.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::board;

namespace
{
class DummyBoardModelActuator : public IBoardModelActuator
{
public:
    virtual void tileAdded(const mtps::vector2dst, SITilePointer&) 
    {
        ++data_;
    }
    virtual void tileRemoved(const mtps::vector2dst, SITilePointer&)
    {
        ++data_;
    }

    virtual void tileMoved(const mtps::vector2dst,
                           const mtps::vector2dst,
                           SITilePointer&)
    {
        ++data_;
    }

    virtual void tileChanged(const mtps::vector2dst,
                             SITilePointer&,
                             const BoardTileData,
                             const BoardTileData)
    {
        ++data_;
    }

    u32 data() const { return data_; }
    void resetData() { data_ = 0U; }
private:
    u32 data_{0U};
};
}  // namespace

TEST_CASE("BoardManager of size 0,0 no actuator", "[board_manager]")
{
    BoardModelComponent board_model_component;

    // Test default constucted is 0 sized.
    CHECK(board_model_component.size() == vector2dst{0U, 0U});

    board_model_component.initialize(vector2dst{0U, 0U}, nullptr);
    CHECK(board_model_component.size() == vector2dst{0U, 0U});
}

TEST_CASE("BoardManager of size 0,0 with actuator", "[board_manager]")
{
    BoardModelComponent board_model_component;

    // Test default constucted is 0 sized.
    CHECK(board_model_component.size() == vector2dst{0U, 0U});

    auto dummy_board_model_actuator = muptr<DummyBoardModelActuator>();

    board_model_component.initialize(vector2dst{0U, 0U},
                                     dummy_board_model_actuator.get());
    CHECK(board_model_component.size() == vector2dst{0U, 0U});
}

TEST_CASE("BoardManager of size 32,32 no actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{4U, 4U};
    BoardModelComponent board_model_component;

    // Test default constucted is 0 sized.
    CHECK(board_model_component.size() == vector2dst{0U, 0U});

    board_model_component.initialize(bm_size, nullptr);
    CHECK(board_model_component.size() == bm_size);

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_model_component.getTile(vector2dst{x, y}) == nullptr);
        }
    }
}

TEST_CASE("BoardManager of size 32,32 with actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{4U, 4U};
    BoardModelComponent board_model_component;

    // Test default constucted is 0 sized.
    CHECK(board_model_component.size() == vector2dst{0U, 0U});

    auto dummy_board_model_actuator = muptr<DummyBoardModelActuator>();

    board_model_component.initialize(bm_size, dummy_board_model_actuator.get());
    CHECK(board_model_component.size() == bm_size);

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_model_component.getTile(vector2dst{x, y}) == nullptr);
        }
    }
}

TEST_CASE("BoardManager get and set dummy titles", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardModelComponent board_model_component;

    board_model_component.initialize(bm_size, nullptr);

    auto tile = msptr<ITile>();

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            board_model_component.setTile(vector2dst{x, y}, tile);
        }
    }

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_model_component.getTile(vector2dst{x, y}) == tile);
        }
    }
}

TEST_CASE("BoardManager get and set with actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardModelComponent board_model_component;
    auto dummy_board_model_actuator = muptr<DummyBoardModelActuator>();

    board_model_component.initialize(bm_size, dummy_board_model_actuator.get());

    auto tile = msptr<ITile>();

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            board_model_component.setTile(vector2dst{x, y}, tile);
        }
    }

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_model_component.getTile(vector2dst{x, y}) == tile);
        }
    }
}

TEST_CASE("BoardManager control with actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardModelComponent board_model_component;
    auto dummy_board_model_actuator = muptr<DummyBoardModelActuator>();

    board_model_component.initialize(bm_size, dummy_board_model_actuator.get());
    CHECK(dummy_board_model_actuator->data() == 0U);

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            auto tile = msptr<ITile>();
            CHECK(tile->data() == 0);
            board_model_component.setTile(vector2dst{x, y}, std::move(tile));
        }
    }

    CHECK(dummy_board_model_actuator->data() == (bm_size.x * bm_size.y));
    dummy_board_model_actuator->resetData();

    CHECK(board_model_component.deleteTile({0, 1}));
    CHECK(dummy_board_model_actuator->data() == 1U);

    CHECK(board_model_component.moveTile({0, 0}, {0, 1}));
    CHECK(dummy_board_model_actuator->data() == 2U);
    CHECK(board_model_component.tileEmpty({0, 0}));
    CHECK_FALSE(board_model_component.tileEmpty({0, 1}));

    CHECK(board_model_component.changeTileData({0,1}, 2));
    CHECK(board_model_component.getTile({1,1})->data() == 0);
    CHECK(board_model_component.getTile({0,1})->data() == 2);
    CHECK(dummy_board_model_actuator->data() == 3U);

    CHECK(board_model_component.swapTileData({0,1}, {1, 1}));
    CHECK(board_model_component.getTile({0,1})->data() == 0);
    CHECK(board_model_component.getTile({1,1})->data() == 2);
    CHECK(dummy_board_model_actuator->data() == 5U);
}
