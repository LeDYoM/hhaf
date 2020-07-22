#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/grouping_property.hpp>
#include <mtypes/include/str.hpp>

using namespace mtps;

struct IntTag
{
    using value_type = int;
};

TEST_CASE("PropertyGroupImpl one element", "[mtypes][property][Grouping]")
{
    PropertyGroupImpl<IntTag> pg;
    auto a = pg.get_property_reference<IntTag>();

    PropertyGroupImpl<IntTag> const pgc;
    auto b = pgc.get_property_reference<IntTag>();
}

TEST_CASE("PropertyGroup one element", "[mtypes][property][Grouping]")
{
    PropertyGroup<IntTag> pg;
    CHECK(pg.set<IntTag>(2));
    CHECK_FALSE(pg.set<IntTag>(2));

    CHECK(pg.set<IntTag>(3));
    CHECK_FALSE(pg.set<IntTag>(3));

    CHECK(pg.get<IntTag>() == 3);
}

struct CharTag
{
    using value_type = char;
};

struct SptrIntTag
{
    using value_type = sptr<s32>;
};

struct StrTag
{
    using value_type = str;
};

TEST_CASE("PropertyGroupImpl four elements", "[mtypes][property][Grouping]")
{
    using TTPropertyGroupImpl =
        PropertyGroupImpl<CharTag, IntTag, StrTag, SptrIntTag>;

    TTPropertyGroupImpl pg;
    auto a1         = pg.get_property_reference<CharTag>();
    auto a2         = pg.get_property_reference<IntTag>();
    auto a3         = pg.get_property_reference<StrTag>();
    auto a4         = pg.get_property_reference<SptrIntTag>();
    auto const sca1 = pg.get_property_reference<CharTag>();
    auto const sca2 = pg.get_property_reference<IntTag>();
    auto const sca3 = pg.get_property_reference<StrTag>();
    auto const sca4 = pg.get_property_reference<SptrIntTag>();

    TTPropertyGroupImpl const pg2;
    auto const ca1 = pg.get_property_reference<CharTag>();
    auto const ca2 = pg.get_property_reference<IntTag>();
    auto const ca3 = pg.get_property_reference<StrTag>();
    auto const ca4 = pg.get_property_reference<SptrIntTag>();
}

TEST_CASE("PropertyGroup four elements", "[mtypes][property][Grouping]")
{
    using TTPropertyGroup = PropertyGroup<CharTag, IntTag, StrTag, SptrIntTag>;

    TTPropertyGroup pg;
    CHECK(pg.set<IntTag>(10000));
    CHECK_FALSE(pg.set<IntTag>(10000));
    CHECK(pg.get<IntTag>() == 10000);

    CHECK(pg.set<IntTag>(10));
    CHECK_FALSE(pg.set<IntTag>(10));
    CHECK(pg.get<IntTag>() == 10);

    CHECK(pg.set<CharTag>(10));
    CHECK_FALSE(pg.set<CharTag>(10));
    CHECK(pg.get<CharTag>() == 10);

    CHECK(pg.set<CharTag>(15));
    CHECK_FALSE(pg.set<CharTag>(15));
    CHECK(pg.get<CharTag>() == 15);

    CHECK_FALSE(pg.set<IntTag>(10));
    CHECK(pg.get<IntTag>() == 10);
}

TEST_CASE("PropertyGroup construction", "[mtypes][property][Grouping]")
{
    using TTPropertyGroup = PropertyGroup<CharTag, IntTag, StrTag, SptrIntTag>;

    TTPropertyGroup pg;

    CHECK(pg.hasChanged<CharTag>());
    CHECK(pg.hasChanged<IntTag>());
    CHECK(pg.hasChanged<StrTag>());
    CHECK(pg.hasChanged<SptrIntTag>());

    CHECK_FALSE(pg.get<CharTag>() == 1);
    CHECK_FALSE(pg.get<IntTag>() == 2);
    CHECK_FALSE(pg.get<StrTag>() == "abc");
    CHECK_FALSE(pg.get<SptrIntTag>() != nullptr);

    CHECK(allHaveChanged(pg));
//    CHECK(anyHasChanged(pg));

    pg.put<CharTag>(1).put<IntTag>(2).put<StrTag>("abc").put<SptrIntTag>(
        msptr<s32>(3));

    CHECK(pg.get<CharTag>() == 1);
    CHECK(pg.get<IntTag>() == 2);
    CHECK(pg.get<StrTag>() == "abc");
    CHECK(*pg.get<SptrIntTag>() == 3);


}
