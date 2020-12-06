#ifndef HAF_TESTS_SHAREABLE_TEST_DATA_INCLUDE_HPP
#define HAF_TESTS_SHAREABLE_TEST_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include <haf/shareddata/include/address.hpp>

class ShareableTestData : public haf::shdata::IShareable
{
public:
    mtps::s32 a;
    mtps::f32 b;
    mtps::str c;

    ~ShareableTestData() override = default;

    static haf::shdata::Address address() { return haf::shdata::Address{"/test/data/"}; }

    bool serialize(mtps::Object& obj) const override
    {
        bool result{true};
        result &= obj.set("a", a);
        result &= obj.set("b", b);
        result &= obj.set("c", c);

        return result;
    }

    bool deserialize(mtps::Object const& obj) override
    {
        bool result = true;
        result &= obj.getValue("a").as(a);
        result &= obj.getValue("b").as(b);
        result &= obj.getValue("c").as(c);

        return result;
    }
};

#endif
