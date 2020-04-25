#include <hlog/include/hlogexport.hpp>
#include <hlog/include/hlog.hpp>

#include <logger/include/cout_commiter.hpp>
#include <logger/include/log.hpp>
#include <logger/include/log_displayer.hpp>
#include <logger/include/log_asserter.hpp>
#include <logger/include/severity_type.hpp>
#include <logger/include/cout_thread_commiter.hpp>

#include <mtypes/include/str.hpp>
#include <hlog/include/hlogexport.hpp>

HLOG_API logger::COutThreadCommiter::InnerData * data_;
