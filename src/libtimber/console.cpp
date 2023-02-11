#include <timber/timber.h>

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <mutex>

using namespace fmt::literals;

namespace {
    constexpr auto thread_style = fmt::fg(fmt::color::forest_green);

    constexpr auto timestamp_style = fmt::fg(fmt::color::dim_gray);

    std::mutex mutex;

    auto level_style(timber::level level) -> fmt::text_style {
        auto color = fmt::color::white;

        switch (level) {
            case timber::level::emergency: color = fmt::color::dark_red; break;
            case timber::level::alert: color = fmt::color::crimson; break;
            case timber::level::critical: color = fmt::color::red; break;
            case timber::level::error: color = fmt::color::orange_red; break;
            case timber::level::warning: color = fmt::color::yellow; break;
            case timber::level::notice: color = fmt::color::lime_green; break;
            case timber::level::info: color = fmt::color::steel_blue; break;
            case timber::level::debug: color = fmt::color::plum; break;
            case timber::level::trace: color = fmt::color::blue_violet; break;
        }

        return fmt::fg(color);
    }
}

namespace timber::console {
    std::FILE* file = stderr;

    auto logger(const log& l) noexcept -> void {
        auto lock = std::scoped_lock<std::mutex>(mutex);

        fmt::print(
            file,

            "{timestamp:%b %d %r} {level:9}{thread:^{thread_width}}{message}\n",

            "timestamp"_a = fmt::styled(l.timestamp, timestamp_style),

            "level"_a = fmt::styled(l.log_level, level_style(l.log_level)),

            "thread"_a = fmt::styled(l.thread_name, thread_style),
            "thread_width"_a =
                l.thread_name.empty() ? 1 : l.thread_name.size() + 2,

            "message"_a = l.message
        );

        fflush(file);
    }
}
