#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/grouping_property.hpp>
#include <htypes/include/str.hpp>

#include <type_traits>
#include <utility>

using namespace htps;

struct IntTag
{
    using value_type = int;
};

TEST_CASE("PropertyGroupImpl one element", "[htypes][property][Grouping]")
{
    PropertyGroupImpl<IntTag> pg;
    auto a = pg.get_property_reference<IntTag>();
    (void)(a);
    PropertyGroupImpl<IntTag> const pgc;
    auto b = pgc.get_property_reference<IntTag>();
    (void)(b);
}

TEST_CASE("PropertyGroupBase one element", "[htypes][property][Grouping]")
{
    PropertyGroupBasic<IntTag> pg;
    CHECK(pg.set<IntTag>(2));
    CHECK_FALSE(pg.set<IntTag>(2));

    CHECK(pg.set<IntTag>(3));
    CHECK_FALSE(pg.set<IntTag>(3));

    CHECK(pg.get<IntTag>() == 3);

    CHECK(allHaveChanged(pg));
    CHECK(anyHasChanged(pg));

    resetHasChanged(pg);

    CHECK_FALSE(pg.hasChanged<IntTag>());

    CHECK_FALSE(allHaveChanged(pg));
    CHECK_FALSE(anyHasChanged(pg));

    CHECK(pg.set<IntTag>(5));
    CHECK_FALSE(pg.set<IntTag>(5));

    CHECK(pg.get<IntTag>() == 5);

    CHECK(allHaveChanged(pg));
    CHECK(anyHasChanged(pg));
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

TEST_CASE("PropertyGroupImpl four elements", "[htypes][property][Grouping]")
{
    using TTPropertyGroupImpl =
        PropertyGroupImpl<CharTag, IntTag, StrTag, SptrIntTag>;

    TTPropertyGroupImpl pg;
    auto a1 = pg.get_property_reference<CharTag>();
    (void)(a1);
    auto a2 = pg.get_property_reference<IntTag>();
    (void)(a2);
    auto a3         = pg.get_property_reference<StrTag>();
    auto a4         = pg.get_property_reference<SptrIntTag>();
    auto const sca1 = pg.get_property_reference<CharTag>();
    (void)(sca1);
    auto const sca2 = pg.get_property_reference<IntTag>();
    (void)(sca2);
    auto const sca3 = pg.get_property_reference<StrTag>();
    auto const sca4 = pg.get_property_reference<SptrIntTag>();

    TTPropertyGroupImpl const pg2;
    auto const ca1 = pg.get_property_reference<CharTag>();
    (void)(ca1);
    auto const ca2 = pg.get_property_reference<IntTag>();
    (void)(ca2);
    auto const ca3 = pg.get_property_reference<StrTag>();
    auto const ca4 = pg.get_property_reference<SptrIntTag>();
}

TEST_CASE("PropertyGroup four elements", "[htypes][property][Grouping]")
{
    using TTPropertyGroup =
        PropertyGroupBasic<CharTag, IntTag, StrTag, SptrIntTag>;

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

TEST_CASE("PropertyGroup changes check", "[htypes][property]")
{
    using TTPropertyGroup =
        PropertyGroupBasic<CharTag, IntTag, StrTag, SptrIntTag>;

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
    CHECK(anyHasChanged(pg));

    resetHasChanged(pg);

    CHECK_FALSE(pg.hasChanged<CharTag>());
    CHECK_FALSE(pg.hasChanged<IntTag>());
    CHECK_FALSE(pg.hasChanged<StrTag>());
    CHECK_FALSE(pg.hasChanged<SptrIntTag>());

    CHECK_FALSE(allHaveChanged(pg));
    CHECK_FALSE(anyHasChanged(pg));

    pg.put<CharTag>(1).put<IntTag>(2).put<StrTag>("abc").put<SptrIntTag>(
        msptr<s32>(3));

    CHECK(pg.hasChanged<CharTag>());
    CHECK(pg.hasChanged<IntTag>());
    CHECK(pg.hasChanged<StrTag>());
    CHECK(pg.hasChanged<SptrIntTag>());

    CHECK(allHaveChanged(pg));
    CHECK(anyHasChanged(pg));

    CHECK(pg.get<CharTag>() == 1);
    CHECK(pg.get<IntTag>() == 2);
    CHECK(pg.get<StrTag>() == "abc");
    CHECK(*pg.get<SptrIntTag>() == 3);

    resetHasChanged(pg);
    CHECK_FALSE(allHaveChanged(pg));
    CHECK_FALSE(anyHasChanged(pg));

    CHECK(pg.set<IntTag>(5));

    CHECK(pg.get<CharTag>() == 1);
    CHECK(pg.get<IntTag>() == 5);
    CHECK(pg.get<StrTag>() == "abc");
    CHECK(*pg.get<SptrIntTag>() == 3);

    CHECK_FALSE(allHaveChanged(pg));
    CHECK(anyHasChanged(pg));

    resetHasChanged(pg);

    CHECK(pg.set<IntTag>(50));

    CHECK_FALSE(pg.readResetHasChanged<CharTag>());
    CHECK_FALSE(pg.readResetHasChanged<StrTag>());
    CHECK_FALSE(pg.readResetHasChanged<SptrIntTag>());
    CHECK(pg.readResetHasChanged<IntTag>());
}

TEST_CASE("PropertyGroupImp one element construction", "[htypes][property]")
{
    using TPropertyGroup = PropertyGroupBasic<IntTag>;
    TPropertyGroup pg(99);

    CHECK(pg.get<IntTag>() == 99);
}

TEST_CASE("PropertyGroup four elements construction", "[htypes][property]")
{
    using TTPropertyGroup =
        PropertyGroupBasic<CharTag, IntTag, StrTag, SptrIntTag>;
    TTPropertyGroup pg('2', 3, "a", msptr<int>(6));

    CHECK(pg.get<CharTag>() == '2');
    CHECK(pg.get<IntTag>() == 3);
    CHECK(pg.get<StrTag>() == "a");
    CHECK(*pg.get<SptrIntTag>() == 6);
}

struct AnotherTag
{
    using value_type = int;
};

TEST_CASE("PropertyGroup::ContainsTag", "[htypes][property]")
{
    using TTPropertyGroup =
        PropertyGroupBasic<CharTag, IntTag, StrTag, SptrIntTag>;
    using TPropertyGroup  = PropertyGroupBasic<IntTag>;
    using ATPropertyGroup = PropertyGroupBasic<AnotherTag, IntTag>;
    using APropertyGroup  = PropertyGroupBasic<AnotherTag>;

    static_assert(TTPropertyGroup::ContainsTag<IntTag>::value);
    static_assert(TTPropertyGroup::ContainsTag<CharTag>::value);
    static_assert(TTPropertyGroup::ContainsTag<StrTag>::value);
    static_assert(TTPropertyGroup::ContainsTag<SptrIntTag>::value);
    static_assert(!TTPropertyGroup::ContainsTag<AnotherTag>::value);

    static_assert(TPropertyGroup::ContainsTag<IntTag>::value);
    static_assert(!TPropertyGroup::ContainsTag<CharTag>::value);
    static_assert(!TPropertyGroup::ContainsTag<StrTag>::value);
    static_assert(!TPropertyGroup::ContainsTag<SptrIntTag>::value);
    static_assert(!TPropertyGroup::ContainsTag<AnotherTag>::value);

    static_assert(ATPropertyGroup::ContainsTag<IntTag>::value);
    static_assert(!ATPropertyGroup::ContainsTag<CharTag>::value);
    static_assert(!ATPropertyGroup::ContainsTag<StrTag>::value);
    static_assert(!ATPropertyGroup::ContainsTag<SptrIntTag>::value);
    static_assert(ATPropertyGroup::ContainsTag<AnotherTag>::value);

    static_assert(!APropertyGroup::ContainsTag<IntTag>::value);
    static_assert(!APropertyGroup::ContainsTag<CharTag>::value);
    static_assert(!APropertyGroup::ContainsTag<StrTag>::value);
    static_assert(!APropertyGroup::ContainsTag<SptrIntTag>::value);
    static_assert(APropertyGroup::ContainsTag<AnotherTag>::value);
}

using FakeSceneNodeProperties = PropertyGroupBasic<IntTag, CharTag>;

class FakeSceneNode : public FakeSceneNodeProperties
{
public:
    void notUsed() {}
};

using EnhancedFakeSceneNodeProperties = PropertyGroupBasic<SptrIntTag, StrTag>;

class EnhancedFakeSceneNode : public FakeSceneNode,
                              public EnhancedFakeSceneNodeProperties
{
public:
    int get() const { return 8; };
    void set(int const) const {};

    using EnhancedFakeSceneNodeProperties::prop;
    using FakeSceneNodeProperties::prop;
};

TEST_CASE("PropertyGroup inheritance", "[htypes][property]")
{
    EnhancedFakeSceneNode efsn;

    efsn.prop<IntTag>().get();
    efsn.prop<StrTag>().get();

    CHECK(efsn.prop<IntTag>().set(2));
    CHECK(efsn.prop<IntTag>().get() == 2);

    efsn.prop<FakeSceneNodeProperties>().put<IntTag>(3).put<CharTag>(5);
    CHECK(efsn.prop<IntTag>().get() == 3);
    CHECK(efsn.prop<CharTag>().get() == 5);

    efsn.prop<EnhancedFakeSceneNodeProperties>()
        .put<StrTag>("world")
        .put<SptrIntTag>(msptr<int>(15));
    CHECK(efsn.prop<StrTag>().get() == "world");
    CHECK(*(efsn.prop<SptrIntTag>().get()) == 15);

    CHECK(efsn.prop<StrTag>().set("hello"));
    CHECK(efsn.prop<StrTag>().get() == "hello");
}

struct IntTagBasic : public BasicPropertyBase<int, IntTagBasic>
{};

struct StrTagBasic : public BasicPropertyBase<str, StrTagBasic>
{};

TEST_CASE("PropertyGroup with basic", "[htypes][property]")
{
    // Check statically that, given IntTagBasic, that contains UseCustomProperty
    // with a PropertyType of BasicProperty, the type returned from
    // get_property_reference is BasicProperty.
    static_assert(std::is_same_v<
                  std::remove_reference_t<
                      decltype(std::declval<PropertyGroupImpl<IntTagBasic>>()
                                   .get_property_reference<IntTagBasic>())>,
                  BasicProperty<IntTagBasic::value_type, IntTagBasic>>);

    PropertyGroupBasic<IntTagBasic> pg;
    CHECK(pg.set<IntTagBasic>(2));
    CHECK_FALSE(pg.set<IntTagBasic>(2));

    CHECK(pg.set<IntTagBasic>(3));
    CHECK_FALSE(pg.set<IntTagBasic>(3));

    CHECK(pg.get<IntTagBasic>() == 3);

    CHECK(pg.set<IntTagBasic>(5));
    CHECK_FALSE(pg.set<IntTagBasic>(5));

    CHECK(pg.get<IntTagBasic>() == 5);
}

TEST_CASE("PropertyGroup with two basic properties", "[htypes][property]")
{
    PropertyGroupBasic<IntTagBasic, StrTagBasic> pg;
    CHECK(pg.set<IntTagBasic>(2));
    CHECK_FALSE(pg.set<IntTagBasic>(2));
    CHECK(pg.set<StrTagBasic>("hi"));
    CHECK_FALSE(pg.set<StrTagBasic>("hi"));

    CHECK(pg.set<IntTagBasic>(3));
    CHECK_FALSE(pg.set<IntTagBasic>(3));

    CHECK(pg.get<IntTagBasic>() == 3);
    CHECK(pg.set<IntTagBasic>(5));
    CHECK_FALSE(pg.set<IntTagBasic>(5));
    CHECK(pg.set<StrTagBasic>("hiloop"));
    CHECK_FALSE(pg.set<StrTagBasic>("hiloop"));

    CHECK(pg.get<IntTagBasic>() == 5);
    CHECK(pg.get<StrTagBasic>() == "hiloop");
}
