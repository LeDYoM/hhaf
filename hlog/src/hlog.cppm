export module hlog;

import htypes;
import logger;

namespace logger
{
export class LogStream
{
    inline static htps::str data;

public:
    htps::str& operator()() { return data; }
};

// Select the commiter
export using FileCOutCommiter       = MixinCommiter<FileCommiter, COutCommiter>;
export using ThreadFileCoutCommiter = ThreadCommiter<FileCOutCommiter>;
// export using CurrentCommiter        = ThreadFileCoutCommiter;
export using CurrentCommiter = COutCommiter;

export constexpr bool kUseLogs{true};

export using CurrentLog            = Log<kUseLogs, LogStream, CurrentCommiter>;
export using CurrentLogInitializer = LogInitializer<CurrentLog>;

export template <bool DisplaySeverity, StringLiteral First>
using DisplayLogGeneral =
    LogDisplayer<CurrentLog, SeverityType, DisplaySeverity, First>;
}  // namespace logger

namespace haf
{
export constexpr bool kDisplaySeverity{true};

export using LogInitializer = logger::CurrentLogInitializer;
export using DisplayLog     = logger::DisplayLogGeneral<kDisplaySeverity, "">;
export using LogAsserter    = logger::LogAsserter<DisplayLog>;

export template <logger::StringLiteral First>
using HafLog = logger::DisplayLogGeneral<kDisplaySeverity, First>;

export template <logger::StringLiteral First>
using HafAssert = logger::LogAsserter<HafLog<First>>;

}  // namespace haf
