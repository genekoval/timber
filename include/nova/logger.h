#pragma once

#include <nova/ext/chrono.h>

#include <chrono>
#include <functional>
#include <sstream>
#include <string>
#include <string_view>

#ifndef LOGGER_MAX_LEVEL
#define LOGGER_MAX_LEVEL nova::logger::level::DEBUG
#endif

#define LOG(lvl) \
    if (lvl > LOGGER_MAX_LEVEL) ;\
    else if (lvl > nova::logger::reporting_level()) ;\
    else if (lvl <= nova::logger::level::OFF) ;\
    else nova::logger::log(__FILE__, __FUNCTION__, __LINE__, lvl).stream()

#define ERROR() \
    LOG(nova::logger::level::ERROR)

#define WARN() \
    LOG(nova::logger::level::WARN)

#define INFO() \
    LOG(nova::logger::level::INFO)

#define DEBUG() \
    LOG(nova::logger::level::DEBUG)

namespace nova::logger {
    constexpr std::string_view DEFAULT_TIME_FORMAT = "%Y/%m/%d %T %Z";
    constexpr nova::ext::chrono::time_type DEFAULT_TIME_TYPE =
        nova::ext::chrono::time_type::local;

    enum level {
        OFF,
        ERROR,
        WARN,
        INFO,
        DEBUG
    };

    std::ostream& operator<<(std::ostream& os, const level& lvl);

    class log {
        std::string filename;
        std::string function_name;
        unsigned int line_number;
        level message_level;
        std::stringstream message_stream;
        nova::ext::chrono::timestamp ts;

        log(const log&);
        log& operator=(const log&);
    public:
        static std::string timestamp_format;
        static nova::ext::chrono::time_type timestamp_type;

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
        nova::ext::chrono::timestamp time() const;
    };

    using write = std::function<void(const log&)>;

    write& log_writer();
    level& reporting_level();

    void color_logger(const log& lg);
    void console_logger(const log& lg);
}
