#include <logger/logger.h>

#include <array>
#include <iostream>

namespace logger {
    constexpr auto levels = std::array<const char*, 5> {
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG",
        "TRACE"
    };

    std::ostream& operator<<(std::ostream& os, level lvl) {
        os << levels[lvl];
        return os;
    }

    log::log(
        std::string_view filename,
        std::string_view function_name,
        std::uint_least32_t line,
        level log_level
    ) :
        filename(filename),
        function_name(function_name),
        line(line),
        log_level(log_level),
        ts(DEFAULT_TIME_FORMAT, DEFAULT_TIME_TYPE)
    {}


    log::~log() { print(std::cerr); }

    auto log::print(std::ostream& os) const -> void {
        os
            << ts << " ["
            << filename << ":"
            << function_name << ":"
            << line << "] "
            << log_level << " "
            << message.rdbuf()
            << std::endl;
    }

    auto reporting_level() -> level& {
        static auto instance = level::info;
        return instance;
    }
}
