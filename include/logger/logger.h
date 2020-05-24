#pragma once

#include <ext/chrono.h>
#include <functional>
#include <sstream>
#include <string>
#include <string_view>

#ifndef LOGGER_MAX_LEVEL
#   define LOGGER_MAX_LEVEL logger::level::DEBUG
#endif

#define LOG(lvl) \
    if (lvl > LOGGER_MAX_LEVEL) ;\
    else if (lvl > logger::reporting_level()) ;\
    else if (lvl <= logger::level::OFF) ;\
    else logger::log(__FILE__, __FUNCTION__, __LINE__, lvl).stream()

#define ERROR() \
    LOG(logger::level::ERROR)

#define WARN() \
    LOG(logger::level::WARN)

#define INFO() \
    LOG(logger::level::INFO)

#define DEBUG() \
    LOG(logger::level::DEBUG)

namespace logger {
    constexpr std::string_view DEFAULT_TIME_FORMAT = "%Y/%m/%d %T %Z";
    constexpr ext::chrono::time_type DEFAULT_TIME_TYPE =
        ext::chrono::time_type::local;

    enum level {
        OFF,
        ERROR,
        WARN,
        INFO,
        DEBUG
    };

    std::ostream& operator<<(std::ostream& os, level lvl);

    class log {
        std::string filename;
        std::string function_name;
        unsigned int line_number;
        level message_level;
        std::stringstream message_stream;
        ext::chrono::timestamp ts;

        log(const log&);
        log& operator=(const log&);
    public:
        static std::string timestamp_format;
        static ext::chrono::time_type timestamp_type;

        log(
            std::string filename,
            std::string function_name,
            unsigned int line_number,
            level message_level
        );
        ~log();

        std::string file() const;
        std::string function() const;
        unsigned int line() const;
        level lvl() const;
        std::stringbuf* message() const;
        std::stringstream& stream();
        ext::chrono::timestamp time() const;
    };

    using write = std::function<void(const log&)>;

    write& log_writer();
    level& reporting_level();

    void color_logger(const log& lg);
    void console_logger(const log& lg);
}
