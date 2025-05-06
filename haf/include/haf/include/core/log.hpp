#ifndef HAF_HLOG_INCLUDE_HPP
#define HAF_HLOG_INCLUDE_HPP

#include <haf/include/core/log_instances.hpp>

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
