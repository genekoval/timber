#include <timber/timber.h>

#include <algorithm>
#include <array>

namespace timber {
    constexpr auto levels = std::array<std::string_view, 5> {
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG",
        "TRACE"
    };

    auto operator<<(std::ostream& os, level lvl) -> std::ostream& {
        os << levels[lvl];
        return os;
    }

    auto parse_level(std::string_view lvl) -> std::optional<level> {
        auto it = std::find(levels.begin(), levels.end(), lvl);

        if (it == levels.end()) return {};

        auto result = std::distance(levels.begin(), it);
        return static_cast<level>(result);
    }

    log::log(level log_level, const source_location& location) :
        log_level(log_level),
        location(location),
        timestamp(clock::now())
    {}

    log::~log() { write(*this); }

    auto reporting_level() -> level& {
        // By default, use the finest logging level.
        static auto instance = static_cast<level>(levels.size());
        return instance;
    }
}
