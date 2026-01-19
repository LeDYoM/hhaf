export module logger_test:log_stream_test;

import logger;
import htypes;

export class LogStreamTest
{
    inline static htps::str data = htps::str{""};

public:
    htps::str& operator()() { return data; }
};
