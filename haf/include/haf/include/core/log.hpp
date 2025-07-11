#ifndef HAF_CORE_LOG_INCLUDE_HPP
#define HAF_CORE_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>

namespace haf
{
extern template LogDisplayer<CurrentLog, SeverityType, kDisplaySeverity>;
extern template logger::LogDisplayer<logger::CurrentLog,
                                     logger::SeverityType,
                                     haf::kDisplaySeverity>;
extern template logger::LogAsserter<
    logger::LogDisplayer<logger::CurrentLog, logger::SeverityType, false>>;

}  // namespace haf
#endif
