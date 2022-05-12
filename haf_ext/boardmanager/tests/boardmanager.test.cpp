#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/iboardmanageractuator.hpp>
#include <boardmanager/include/itile.hpp>

using namespace htps;
using namespace haf;
using namespace haf::board;

namespace
{
class DummyBoardModelActuator : public IBoardManagerActuator
{
public:
    virtual void tileAdded(const htps::vector2dst, SITilePointer&) { ++data_; }
    virtual void tileRemoved(const htps::vector2dst, SITilePointer&)
    {
        ++data_;
    }

    virtual void tileMoved(const htps::vector2dst,
                           const htps::vector2dst,
                           SITilePointer&)
    {
        ++data_;
    }

    virtual void tileChanged(const htps::vector2dst,
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

TEST_CASE("BoardManager of size 0 and 0 no actuator", "[board_manager]")
{
    BoardManager board_manager_component;

    // Test default constucted is 0 sized.
    CHECK(board_manager_component.size() == vector2dst{0U, 0U});

    board_manager_component.initialize(vector2dst{0U, 0U}, nullptr);
    CHECK(board_manager_component.size() == vector2dst{0U, 0U});
}

TEST_CASE("BoardManager of size 0 and 0 with actuator", "[board_manager]")
{
    BoardManager board_manager_component;

    // Test default constucted is 0 sized.
    CHECK(board_manager_component.size() == vector2dst{0U, 0U});

    auto dummy_board_manager_actuator = muptr<DummyBoardModelActuator>();

    board_manager_component.initialize(vector2dst{0U, 0U},
                                       dummy_board_manager_actuator.get());
    CHECK(board_manager_component.size() == vector2dst{0U, 0U});
}

TEST_CASE("BoardManager of size 32 and 32 no actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{4U, 4U};
    BoardManager board_manager_component;

    // Test default constucted is 0 sized.
    CHECK(board_manager_component.size() == vector2dst{0U, 0U});

    board_manager_component.initialize(bm_size, nullptr);
    CHECK(board_manager_component.size() == bm_size);

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_manager_component.getTile(vector2dst{x, y}) == nullptr);
        }
    }
}

TEST_CASE("BoardManager of size 32 and 32 with actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{4U, 4U};
    BoardManager board_manager_component;

    // Test default constucted is 0 sized.
    CHECK(board_manager_component.size() == vector2dst{0U, 0U});

    auto dummy_board_manager_actuator = muptr<DummyBoardModelActuator>();

    board_manager_component.initialize(bm_size,
                                       dummy_board_manager_actuator.get());
    CHECK(board_manager_component.size() == bm_size);

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_manager_component.getTile(vector2dst{x, y}) == nullptr);
        }
    }
}

TEST_CASE("BoardManager get and set dummy titles", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardManager board_manager_component;

    board_manager_component.initialize(bm_size, nullptr);

    auto tile = msptr<ITile>();

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            board_manager_component.setTile(vector2dst{x, y}, tile);
        }
    }

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_manager_component.getTile(vector2dst{x, y}) == tile);
        }
    }
}

TEST_CASE("BoardManager get and set with actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardManager board_manager_component;
    auto dummy_board_manager_actuator = muptr<DummyBoardModelActuator>();

    board_manager_component.initialize(bm_size,
                                       dummy_board_manager_actuator.get());

    auto tile = msptr<ITile>();

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            board_manager_component.setTile(vector2dst{x, y}, tile);
        }
    }

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            CHECK(board_manager_component.getTile(vector2dst{x, y}) == tile);
        }
    }
}

TEST_CASE("BoardManager control with actuator", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardManager board_manager_component;
    auto dummy_board_manager_actuator = muptr<DummyBoardModelActuator>();

    board_manager_component.initialize(bm_size,
                                       dummy_board_manager_actuator.get());
    CHECK(dummy_board_manager_actuator->data() == 0U);

    for (auto x = 0U; x < bm_size.x; ++x)
    {
        for (auto y = 0U; y < bm_size.y; ++y)
        {
            auto tile = msptr<ITile>();
            CHECK(tile->value() == 0);
            board_manager_component.setTile(vector2dst{x, y}, htps::move(tile));
        }
    }

    CHECK(dummy_board_manager_actuator->data() == (bm_size.x * bm_size.y));
    dummy_board_manager_actuator->resetData();

    CHECK(board_manager_component.deleteTile({0, 1}));
    CHECK(dummy_board_manager_actuator->data() == 1U);

    CHECK(board_manager_component.moveTile({0, 0}, {0, 1}));
    CHECK(dummy_board_manager_actuator->data() == 2U);
    CHECK(board_manager_component.tileEmpty({0, 0}));
    CHECK_FALSE(board_manager_component.tileEmpty({0, 1}));

    CHECK(board_manager_component.changeTileData({0, 1}, 2));
    CHECK(board_manager_component.getTile({1, 1})->value() == 0);
    CHECK(board_manager_component.getTile({0, 1})->value() == 2);
    CHECK(dummy_board_manager_actuator->data() == 3U);

    CHECK(board_manager_component.swapTileData({0, 1}, {1, 1}));
    CHECK(board_manager_component.getTile({0, 1})->value() == 0);
    CHECK(board_manager_component.getTile({1, 1})->value() == 2);
    CHECK(dummy_board_manager_actuator->data() == 5U);
}

TEST_CASE("BoardManager::validCoords", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardManager board_manager_component;
    board_manager_component.initialize(bm_size, nullptr);

    for (auto x = 0U; x < 10U; ++x)
    {
        for (auto y = 0U; y < 10U; ++y)
        {
            if (x < 8U && y < 8U)
            {
                CHECK(board_manager_component.validCoords({x, y}));
            }
            else
            {
                CHECK_FALSE(board_manager_component.validCoords({x, y}));
            }
        }
    }
}

TEST_CASE("BoardManager background data", "[board_manager]")
{
    constexpr vector2dst bm_size = vector2dst{8U, 8U};
    BoardManager board_manager_component;
    board_manager_component.initialize(bm_size, nullptr);

    for (auto x = 0U; x < 10U; ++x)
    {
        for (auto y = 0U; y < 10U; ++y)
        {
            CHECK(board_manager_component.backgroundData({x, y}) ==
                  BoardManager::BackgroundData{});
        }
    }

    board_manager_component.setBackgroundFunction([](const auto& position) {
        return static_cast<BoardManager::BackgroundData>(position.x *
                                                         position.y);
    });

    for (auto x = 0U; x < 10U; ++x)
    {
        for (auto y = 0U; y < 10U; ++y)
        {
            if (x < 8U && y < 8U)
            {
                CHECK(board_manager_component.backgroundData({x, y}) ==
                      static_cast<BoardManager::BackgroundData>(x * y));
            }
            else
            {
                CHECK(board_manager_component.backgroundData({x, y}) ==
                      BoardManager::BackgroundData{});
            }
        }
    }
}
