#include <logger.h>

#include <nova/color.h>

#include <iostream>
#include <sstream>

using logger::level;
using logger::log;
using logger::write;
using nova::ext::chrono::time_type;
using nova::ext::chrono::timestamp;
using std::cerr;
using std::endl;
using std::ostream;
using std::string;
using std::stringbuf;
using std::stringstream;

string log::timestamp_format = string(DEFAULT_TIME_FORMAT);
time_type log::timestamp_type = DEFAULT_TIME_TYPE;

ostream& logger::operator<<(ostream& os, const level& lvl) {
    switch (lvl) {
        case level::OFF  : os << "";      break;
        case level::ERROR: os << "ERROR"; break;
        case level::WARN : os << "WARN "; break;
        case level::INFO : os << "INFO "; break;
        case level::DEBUG: os << "DEBUG"; break;
    }
    return os;
}

log::log(
    string filename,
    string function_name,
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

string log::file() const { return filename; }

string log::function() const { return function_name; }

unsigned int log::line() const { return line_number; }

level log::lvl() const { return message_level; }

stringbuf* log::message() const { return message_stream.rdbuf(); }

stringstream& log::stream() { return message_stream; }

timestamp log::time() const { return ts; }

write& logger::log_writer() {
    static write instance = console_logger;
    return instance;
}

level& logger::reporting_level() {
    static level instance(level::INFO);
    return instance;
}

void logger::color_logger(const log& lg) {
    using termcolor::color;
    using termcolor::format;

    color clr;

    switch (lg.lvl()) {
        case level::OFF  : clr = color::white;  break;
        case level::ERROR: clr = color::red;    break;
        case level::WARN : clr = color::yellow; break;
        case level::INFO : clr = color::blue;   break;
        case level::DEBUG: clr = color::green;  break;
    }

    cerr
        // Print timestamp.
        << lg.time() << " "

        // Print level.
        << termcolor::set(format::bold, clr) << lg.lvl()
        << termcolor::reset()

        // Print logging location information.
        << " ["
        << termcolor::set(color::green) << lg.file()
        << termcolor::reset() << ":"
        << termcolor::set(color::green) << lg.function()
        << termcolor::reset() << ":"
        << termcolor::set(color::green) << lg.line()
        << termcolor::reset() << "] "

        // Print message.
        << lg.message()

        << endl;
}

void logger::console_logger(const log& lg) {
    cerr
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

        << endl;
}
