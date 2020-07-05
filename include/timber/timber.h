#pragma once

#include <chrono>
#include <experimental/source_location>
#include <optional>
#include <sstream>
#include <string_view>

namespace timber {
    using clock = std::chrono::system_clock;
    using source_location = std::experimental::source_location;

    enum level {
        error,
        warn,
        info,
        debug,
        trace
    };

    auto operator<<(std::ostream& os, level lvl) -> std::ostream&;

    auto parse_level(std::string_view lvl) -> std::optional<level>;

    struct log {
        const level log_level;
        const source_location location;
        std::ostringstream stream;
        const clock::time_point timestamp;

        log(
            level log_level,
            const source_location& location = source_location::current()
        );
        ~log();
    };

    auto reporting_level() -> level&;

    auto handle_log(const log& lg) noexcept -> void;
}
