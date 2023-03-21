#ifndef HAF_HLOG_LOG_STREAM_TEST_INCLUDE_HPP
#define HAF_HLOG_LOG_STREAM_TEST_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <logger/include/null_commiter.hpp>

class LogStreamTest
{
    inline static htps::str data = htps::str{""};

public:
    htps::str& operator()() { return data; }
};

using LogTestNullCommit =
    logger::Log<true, LogStreamTest, logger::NullCommiter>;

 #endif
