#include <timber/timber.h>

#include <fmt/chrono.h>

using namespace std::chrono_literals;

using std::chrono::duration_cast;

namespace {
    auto format_duration(std::chrono::nanoseconds duration) -> std::string {
        const auto hms = std::chrono::hh_mm_ss(duration);

        if (hms.hours().count() > 0) {
            return fmt::format(
                "{} {} {}",
                hms.hours(),
                hms.minutes(),
                hms.seconds()
            );
        }

        if (hms.minutes().count() > 0) {
            return fmt::format("{} {}", hms.minutes(), hms.seconds());
        }

        if (hms.seconds().count() > 0) {
            return fmt::format("{}", hms.seconds());
        }

        const auto milliseconds =
            duration_cast<std::chrono::milliseconds>(duration);

        if (milliseconds.count() > 0) return fmt::format("{}", milliseconds);

        const auto microseconds =
            duration_cast<std::chrono::microseconds>(duration);

        if (microseconds.count() > 0) return fmt::format("{}", microseconds);

        return fmt::format("{}", duration);
    }
}

namespace timber {
    timer::timer(level log_level, const source_location& location) :
        log_level(log_level),
        location(location),
        identifier(fmt::format("{} took", location.function_name())),
        start(clock::now()) {}

    timer::timer(
        std::string_view identifier,
        level log_level,
        const source_location& location
    ) :
        log_level(log_level),
        location(location),
        identifier(identifier),
        start(clock::now()) {}

    timer::~timer() {
        if (log_on_destruct_enabled) stop();
    }

    auto timer::log_on_destruct(bool enabled) -> void {
        log_on_destruct_enabled = enabled;
    }

    auto timer::reset() -> void { start = clock::now(); }

    auto timer::stop() noexcept -> void {
        if (logged) return;

        write_log();
        logged = true;
    }

    auto timer::write_log() noexcept -> void {
        if (log_level > reporting_level || !log_handler) return;

        const auto duration = clock::now() - start;

        log(log_level, location)
            .write("{} {}", identifier, format_duration(duration));
    }

    auto auto_timer(level log_level, const source_location& location) -> timer {
        auto result = timer(log_level, location);
        result.log_on_destruct(true);
        return result;
    }

    auto auto_timer(
        std::string_view identifier,
        level log_level,
        const source_location& location
    ) -> timer {
        auto result = timer(identifier, log_level, location);
        result.log_on_destruct(true);
        return result;
    }
}
