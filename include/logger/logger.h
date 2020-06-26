#pragma once

#include <ext/chrono.h>
#include <sstream>
#include <string>
#include <string_view>

#ifndef LOGGER_MAX_LEVEL
#   define LOGGER_MAX_LEVEL logger::level::trace
#endif

#define LOG(lvl) \
    if (lvl > LOGGER_MAX_LEVEL) ;\
    else if (lvl > logger::reporting_level()) ;\
    else logger::log(__FILE__, __FUNCTION__, __LINE__, lvl).message

#define ERROR() \
    LOG(logger::level::error)

#define WARN() \
    LOG(logger::level::warn)

#define INFO() \
    LOG(logger::level::info)

#define DEBUG() \
    LOG(logger::level::debug)

#define TRACE() \
    LOG(logger::level::trace)

namespace logger {
    constexpr auto DEFAULT_TIME_FORMAT = "%Y-%m-%d %T %Z";
    constexpr auto DEFAULT_TIME_TYPE = ext::chrono::time_type::local;

    enum level {
        error,
        warn,
        info,
        debug,
        trace
    };

    std::ostream& operator<<(std::ostream& os, level lvl);

    class log {
        log(const log&);
        log& operator=(const log&);
    public:
        const std::string filename;
        const std::string function_name;
        const std::uint_least32_t line;
        const level log_level;
        std::stringstream message;
        const ext::chrono::timestamp ts;

        log(
            std::string_view filename,
            std::string_view function_name,
            std::uint_least32_t line,
            level log_level
        );
        ~log();

        auto print(std::ostream& os) const -> void;
    };

    auto reporting_level() -> level&;
}
