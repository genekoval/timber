#include <logger/logger.h>

#include <array>
#include <iostream>
#include <termcolor/termcolor>
#include <sstream>

namespace logger {
    constexpr auto levels = std::array<const char*, 5>{
        "OFF",
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG"
    };

    std::string log::timestamp_format = std::string(DEFAULT_TIME_FORMAT);
    ext::chrono::time_type log::timestamp_type = DEFAULT_TIME_TYPE;

    std::ostream& operator<<(std::ostream& os, level lvl) {
        os << levels[lvl];
        return os;
    }

    log::log(
        std::string filename,
        std::string function_name,
        unsigned int line_number,
        level message_level
    ) :
        filename(filename),
        function_name(function_name),
        line_number(line_number),
        message_level(message_level),
        ts(timestamp_format, timestamp_type)
    {}

    log::~log() {
        if (log_writer()) log_writer()(*this);
    }

    std::string log::file() const { return filename; }

    std::string log::function() const { return function_name; }

    unsigned int log::line() const { return line_number; }

    level log::lvl() const { return message_level; }

    std::stringbuf* log::message() const { return message_stream.rdbuf(); }

    std::stringstream& log::stream() { return message_stream; }

    ext::chrono::timestamp log::time() const { return ts; }

    write& log_writer() {
        static write instance = console_logger;
        return instance;
    }

    level& reporting_level() {
        static auto instance = level::INFO;
        return instance;
    }

    void color_logger(const log& lg) {
        using namespace termcolor;

        color clr;

        switch (lg.lvl()) {
            case level::OFF  : clr = color::white;  break;
            case level::ERROR: clr = color::red;    break;
            case level::WARN : clr = color::yellow; break;
            case level::INFO : clr = color::blue;   break;
            case level::DEBUG: clr = color::green;  break;
        }

        std::cerr
            // Print timestamp.
            << lg.time() << " "

            // Print level.
            << set(format::bold, clr) << lg.lvl()
            << reset()

            // Print logging location information.
            << " ["
            << set(color::green) << lg.file()
            << reset() << ":"
            << set(color::green) << lg.function()
            << reset() << ":"
            << set(color::green) << lg.line()
            << reset() << "] "

            // Print message.
            << lg.message()

            << std::endl;
    }

    void console_logger(const log& lg) {
        std::cerr
            // Print bullet point.
            << "- "

            // Print timestamp.
            << lg.time()

            // Print logging location information.
            << " ("
            << lg.file()
            << ":"
            << lg.function()
            << ":"
            << lg.line()

            // Print level.
            << ") "
            << lg.lvl()

            // Print message.
            << " " << lg.message()

            << std::endl;
    }
}
