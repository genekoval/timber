#include <timber/timber.h>

#include <algorithm>
#include <array>
#include <iostream>

namespace timber {
    constexpr auto levels = std::array<std::string_view, 5> {
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG",
        "TRACE"
    };

    auto operator<<(std::ostream& os, level lvl) -> std::ostream& {
        os << levels[static_cast<int>(lvl)];
        return os;
    }

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
        timestamp(clock::now())
    {}

    log::~log() {
        if (!log_handler) return;
        log_handler(*this);
    }

    auto console_logger(const log& l) noexcept -> void {
        std::cerr
            << "[" << l.log_level << "] "
            << l.stream.str()
            << std::endl;
    }

    log_handler_t log_handler = nullptr;

    level reporting_level = static_cast<level>(levels.size() -1);
}
