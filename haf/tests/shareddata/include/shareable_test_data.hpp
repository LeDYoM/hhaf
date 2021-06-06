#ifndef HAF_TESTS_SHAREABLE_TEST_DATA_INCLUDE_HPP
#define HAF_TESTS_SHAREABLE_TEST_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>

class ShareableTestData : public haf::shdata::IShareable
{
public:
    htps::s32 a;
    htps::f32 b;
    htps::str c;

    ~ShareableTestData() override = default;

    static haf::shdata::Address address() { return haf::shdata::Address{"/test/data/"}; }

    bool serialize(htps::Object& obj) const override
    {
        bool result{true};
        result &= obj.set("a", a);
        result &= obj.set("b", b);
        result &= obj.set("c", c);

        return result;
    }

    bool deserialize(htps::Object const& obj) override
    {
        bool result = true;
        result &= obj.getValue("a").as(a);
        result &= obj.getValue("b").as(b);
        result &= obj.getValue("c").as(c);

        return result;
    }
};

#endif
