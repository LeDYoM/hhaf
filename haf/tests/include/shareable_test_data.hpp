#pragma once

#ifndef HAF_TESTS_SHAREABLE_TEST_DATA_INCLUDE_HPP
#define HAF_TESTS_SHAREABLE_TEST_DATA_INCLUDE_HPP

#include <haf/shareddata/include/ishareable.hpp>

class ShareableTest : public haf::shdata::IShareable
{
public:
    ShareableTest(int const data) : data_{data} {}
    int& data() { return data_; }
    int const& data() const { return data_; }

private:
    int data_;
};

#endif
