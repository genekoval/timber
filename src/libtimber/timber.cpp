#include <timber/timber.h>

#include <algorithm>
#include <array>

namespace timber {
    constexpr auto levels = std::array {
        "EMERGENCY",
        "ALERT",
        "CRITICAL",
        "ERROR",
        "WARNING",
        "NOTICE",
        "INFO",
        "DEBUG",
        "TRACE"
    };

    auto parse_level(std::string_view lvl) -> std::optional<level> {
        // Perform a case-insensitive search for the specified level.
        auto it = std::find_if(levels.begin(), levels.end(), [lvl](
            std::string_view current
        ) -> bool {
            return std::equal(
                current.begin(), current.end(),
                lvl.begin(), lvl.end(),
                [](char a, char b) {
                    return std::toupper(a) == std::toupper(b);
                });
        });

        if (it == levels.end()) return {};

        auto result = std::distance(levels.begin(), it);
        return static_cast<level>(result);
    }

    log::log(level log_level, const source_location& location) :
        log_level(log_level),
        location(location),
        thread_id(std::this_thread::get_id()),
        thread_name(timber::thread_name),
        timestamp(clock::now())
    {}

    log::~log() {
        log_handler(*this);
    }

    log_handler_t log_handler = nullptr;

    level reporting_level = static_cast<level>(levels.size() -1);

    thread_local std::string thread_name;
}
