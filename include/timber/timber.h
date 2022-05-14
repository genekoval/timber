#pragma once

#include <chrono>
#include <experimental/source_location>
#include <fmt/format.h>
#include <optional>
#include <string_view>

namespace timber {
    using source_location = std::experimental::source_location;

    enum class level {
        emergency,
        alert,
        critical,
        error,
        warning,
        notice,
        info,
        debug,
        trace
    };

    auto parse_level(std::string_view lvl) -> std::optional<level>;

    struct log {
        using clock = std::chrono::system_clock;
        const level log_level;
        const source_location location;
        std::string message;
        const clock::time_point timestamp;

        log(
            level log_level,
            const source_location& location = source_location::current()
        );

        ~log();

        template <typename ...Args>
        auto write(std::string_view format_string, Args&&... args) -> void {
            message = fmt::format(
                fmt::runtime(format_string),
                std::forward<Args>(args)...
            );
        }
    };

    class timer {
        using clock = std::chrono::steady_clock;

        const level log_level;
        const source_location location;
        const std::string identifier;

        bool log_on_destruct_enabled = false;
        bool logged = false;
        clock::time_point start;

        auto write_log() noexcept -> void;
    public:
        timer(
            level log_level = level::debug,
            const source_location& location = source_location::current()
        );

        timer(
            std::string_view identifier,
            level log_level = level::debug,
            const source_location& location = source_location::current()
        );

        ~timer();

        auto log_on_destruct(bool enabled) -> void;

        auto reset() -> void;

        auto stop() noexcept -> void;
    };

    auto auto_timer(
        level log_level = level::debug,
        const source_location& location = source_location::current()
    ) -> timer;

    auto auto_timer(
        std::string_view identifier,
        level log_level = level::debug,
        const source_location& location = source_location::current()
    ) -> timer;

    using log_handler_t = auto (*)(const log&) noexcept -> void;

    extern log_handler_t log_handler;

    extern level reporting_level;

    auto console_logger(const log& l) noexcept -> void;
}

template <>
struct fmt::formatter<timber::level> : formatter<std::string_view> {
    template <typename FormatContext>
    auto format(timber::level level, FormatContext& ctx) {
        auto string = std::string_view();

        switch (level) {
            case timber::level::emergency: string = "emergency"; break;
            case timber::level::alert: string = "alert"; break;
            case timber::level::critical: string = "critical"; break;
            case timber::level::error: string = "error"; break;
            case timber::level::warning: string = "warning"; break;
            case timber::level::notice: string = "notice"; break;
            case timber::level::info: string = "info"; break;
            case timber::level::debug: string = "debug"; break;
            case timber::level::trace: string = "trace"; break;
        }

        return formatter<std::string_view>::format(string, ctx);
    }
};
