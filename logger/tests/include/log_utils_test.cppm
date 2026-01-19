export module logger_test:log_utils;

import :log_stream_test;
import logger;

export using LogTestNullCommit =
    logger::Log<true, LogStreamTest, logger::NullCommiter>;

export using LogTestThreadNullCommit = logger::
    Log<true, LogStreamTest, logger::ThreadCommiter<logger::NullCommiter>>;
