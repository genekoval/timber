#include <nova/logger.h>

#include <nova/color.h>

#include <iostream>
#include <sstream>

using nova::logger::level;
using nova::logger::log;
using nova::logger::write;
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

ostream& nova::logger::operator<<(ostream& os, const level& lvl) {
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

write& nova::logger::log_writer() {
    static write instance = console_logger;
    return instance;
}

level& nova::logger::reporting_level() {
    static level instance(level::INFO);
    return instance;
}

void nova::logger::color_logger(const log& lg) {
    using namespace nova::termcolor;

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

        << endl;
}

void nova::logger::console_logger(const log& lg) {
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
