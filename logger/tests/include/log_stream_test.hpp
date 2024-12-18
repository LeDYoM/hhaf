#ifndef LOGGER_TEST_LOGGERS_INCLUDE_HPP
#define LOGGER_TEST_LOGGERS_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <logger/include/commiters/null_commiter.hpp>
#include <logger/include/commiters/thread_commiter.hpp>
#include <logger/include/log.hpp>

class LogStreamTest
{
    inline static htps::str data = htps::str{""};

public:
    htps::str& operator()() { return data; }
};

using LogTestNullCommit =
    logger::Log<true, LogStreamTest, logger::NullCommiter>;

using LogTestThreadNullCommit =
    logger::Log<true, LogStreamTest, logger::ThreadCommiter<logger::NullCommiter>>;

 #endif
